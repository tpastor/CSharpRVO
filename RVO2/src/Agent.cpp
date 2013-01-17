/*
 *  Agent.cpp
 *  RVO2 Library.
 *  
 *  
 *  Copyright (C) 2008-10 University of North Carolina at Chapel Hill.
 *  All rights reserved.
 *  
 *  Permission to use, copy, modify, and distribute this software and its
 *  documentation for educational, research, and non-profit purposes, without
 *  fee, and without a written agreement is hereby granted, provided that the
 *  above copyright notice, this paragraph, and the following four paragraphs
 *  appear in all copies.
 *  
 *  Permission to incorporate this software into commercial products may be
 *  obtained by contacting the University of North Carolina at Chapel Hill.
 *  
 *  This software program and documentation are copyrighted by the University of
 *  North Carolina at Chapel Hill. The software program and documentation are
 *  supplied "as is", without any accompanying services from the University of
 *  North Carolina at Chapel Hill or the authors. The University of North
 *  Carolina at Chapel Hill and the authors do not warrant that the operation of
 *  the program will be uninterrupted or error-free. The end-user understands
 *  that the program was developed for research purposes and is advised not to
 *  rely exclusively on the program for any reason.
 *  
 *  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR ITS
 *  EMPLOYEES OR THE AUTHORS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
 *  SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
 *  ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE
 *  UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE AUTHORS HAVE BEEN ADVISED
 *  OF THE POSSIBILITY OF SUCH DAMAGE.
 *  
 *  THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY
 *  DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY
 *  STATUTORY WARRANTY OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS
 *  ON AN "AS IS" BASIS, AND THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND
 *  THE AUTHORS HAVE NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
 *  ENHANCEMENTS, OR MODIFICATIONS.
 *  
 *  Please send all BUG REPORTS to:
 *  
 *  geom@cs.unc.edu
 *  
 *  The authors may be contacted via:
 *  
 *  Jur van den Berg, Stephen J. Guy, Jamie Snape, Ming C. Lin, and
 *  Dinesh Manocha
 *  Dept. of Computer Science
 *  Frederick P. Brooks Jr. Computer Science Bldg.
 *  3175 University of N.C.
 *  Chapel Hill, N.C. 27599-3175
 *  United States of America
 *  
 *  http://gamma.cs.unc.edu/RVO2/
 *  
 */

#include "Agent.h"

#include "KdTree.h"
#include "Obstacle.h"

namespace RVO
{
  Agent::Agent(RVOSimulator* sim) : agentNeighbors_(), maxNeighbors_(0), maxSpeed_(0.0f), neighborDist_(0.0f), newVelocity_(), obstacleNeighbors_(), orcaLines_(), position_(), prefVelocity_(), radius_(0.0f), sim_(sim), timeHorizon_(0.0f), timeHorizonObst_(0.0f), velocity_(), id_(0)
  {
  }

  Agent::~Agent()
  {
  }

  void Agent::computeNeighbors()
  {
    obstacleNeighbors_.clear();
    float rangeSq = sqr(timeHorizonObst_ * maxSpeed_ + radius_);
    sim_->kdTree_->computeObstacleNeighbors(this, rangeSq);

    agentNeighbors_.clear();
    if (maxNeighbors_ > 0) {
      rangeSq = sqr(neighborDist_);
      sim_->kdTree_->computeAgentNeighbors(this, rangeSq);
    }
  }

  /* Search for the best new velocity. */
  void Agent::computeNewVelocity()
  {
    orcaLines_.clear();

    const float invTimeHorizonObst = 1.0f / timeHorizonObst_;

    /* Create obstacle ORCA lines. */
    for (size_t i = 0; i < obstacleNeighbors_.size(); ++i) {
      
      const Obstacle* obstacle1 = obstacleNeighbors_[i].second;
      const Obstacle* obstacle2 = obstacle1->nextObstacle;

      const Vector2 relativePosition1 = obstacle1->point_ - position_;
      const Vector2 relativePosition2 = obstacle2->point_ - position_;
      
      /* 
       * Check if velocity obstacle of obstacle is already taken care of by
       * previously constructed obstacle ORCA lines.
       */
      bool alreadyCovered = false;

      for (size_t j = 0; j < orcaLines_.size(); ++j) {
        if (det(invTimeHorizonObst * relativePosition1 - orcaLines_[j].point, orcaLines_[j].direction) - invTimeHorizonObst * radius_ >= -RVO_EPSILON && det(invTimeHorizonObst * relativePosition2 - orcaLines_[j].point, orcaLines_[j].direction) - invTimeHorizonObst * radius_ >=  -RVO_EPSILON) {
          alreadyCovered = true;
          break;
        }
      }

      if (alreadyCovered) {
        continue;
      }

      /* Not yet covered. Check for collisions. */
      
      const float distSq1 = absSq(relativePosition1);
      const float distSq2 = absSq(relativePosition2);

      const float radiusSq = sqr(radius_);

      const Vector2 obstacleVector = obstacle2->point_ - obstacle1->point_;
      const float s = (-relativePosition1 * obstacleVector) / absSq(obstacleVector);
      const float distSqLine = absSq(-relativePosition1 - s * obstacleVector);

      Line line;

      if (s < 0 && distSq1 <= radiusSq) {
        /* Collision with left vertex. Ignore if non-convex. */
        if (obstacle1->isConvex_) { 
          line.point = Vector2(0,0);
          line.direction = normalize(Vector2(-relativePosition1.y(), relativePosition1.x()));
          orcaLines_.push_back(line);
        }
        continue;
      } else if (s > 1 && distSq2 <= radiusSq) {
        /* Collision with right vertex. Ignore if non-convex 
         * or if it will be taken care of by neighoring obstace */
        if (obstacle2->isConvex_ && det(relativePosition2, obstacle2->unitDir_) >= 0) { 
          line.point = Vector2(0,0);
          line.direction = normalize(Vector2(-relativePosition2.y(), relativePosition2.x()));
          orcaLines_.push_back(line);
        }
        continue;
      } else if (s >= 0 && s < 1 && distSqLine <= radiusSq) {
        /* Collision with obstacle segment. */
        line.point = Vector2(0,0);
        line.direction = -obstacle1->unitDir_;
        orcaLines_.push_back(line);
        continue;
      } 
      
      /* 
       * No collision.  
       * Compute legs. When obliquely viewed, both legs can come from a single
       * vertex. Legs extend cut-off line when nonconvex vertex.
       */

      Vector2 leftLegDirection, rightLegDirection;
      
      if (s < 0 && distSqLine <= radiusSq) {
        /*
         * Obstacle viewed obliquely so that left vertex
         * defines velocity obstacle.
         */
        if (!obstacle1->isConvex_) {
          /* Ignore obstacle. */
          continue;
        }

        obstacle2 = obstacle1;

        const float leg1 = std::sqrt(distSq1 - radiusSq);
        leftLegDirection = Vector2(relativePosition1.x() * leg1 - relativePosition1.y() * radius_, relativePosition1.x() * radius_ + relativePosition1.y() * leg1) / distSq1;
        rightLegDirection = Vector2(relativePosition1.x() * leg1 + relativePosition1.y() * radius_, -relativePosition1.x() * radius_ + relativePosition1.y() * leg1) / distSq1;
      } else if (s > 1 && distSqLine <= radiusSq) {
        /*
         * Obstacle viewed obliquely so that
         * right vertex defines velocity obstacle.
         */
        if (!obstacle2->isConvex_) {
          /* Ignore obstacle. */
          continue;
        }

        obstacle1 = obstacle2;

        const float leg2 = std::sqrt(distSq2 - radiusSq);
        leftLegDirection = Vector2(relativePosition2.x() * leg2 - relativePosition2.y() * radius_, relativePosition2.x() * radius_ + relativePosition2.y() * leg2) / distSq2;
        rightLegDirection = Vector2(relativePosition2.x() * leg2 + relativePosition2.y() * radius_, -relativePosition2.x() * radius_ + relativePosition2.y() * leg2) / distSq2;
      } else {
        /* Usual situation. */
        if (obstacle1->isConvex_) {
          const float leg1 = std::sqrt(distSq1 - radiusSq);
          leftLegDirection = Vector2(relativePosition1.x() * leg1 - relativePosition1.y() * radius_, relativePosition1.x() * radius_ + relativePosition1.y() * leg1) / distSq1;
        } else {
          /* Left vertex non-convex; left leg extends cut-off line. */
          leftLegDirection = -obstacle1->unitDir_;
        }

        if (obstacle2->isConvex_) {
          const float leg2 = std::sqrt(distSq2 - radiusSq);
          rightLegDirection = Vector2(relativePosition2.x() * leg2 + relativePosition2.y() * radius_, -relativePosition2.x() * radius_ + relativePosition2.y() * leg2) / distSq2;
        } else {
          /* Right vertex non-convex; right leg extends cut-off line. */
          rightLegDirection = obstacle1->unitDir_;
        }
      }

      /* 
       * Legs can never point into neighboring edge when convex vertex,
       * take cutoff-line of neighboring edge instead. If velocity projected on
       * "foreign" leg, no constraint is added. 
       */

      const Obstacle* const leftNeighbor = obstacle1->prevObstacle;
      
      bool isLeftLegForeign = false;
      bool isRightLegForeign = false;

      if (obstacle1->isConvex_ && det(leftLegDirection, -leftNeighbor->unitDir_) >= 0.0f) {
        /* Left leg points into obstacle. */
        leftLegDirection = -leftNeighbor->unitDir_;
        isLeftLegForeign = true;
      }

      if (obstacle2->isConvex_ && det(rightLegDirection, obstacle2->unitDir_) <= 0.0f) {
        /* Right leg points into obstacle. */
        rightLegDirection = obstacle2->unitDir_;
        isRightLegForeign = true;
      }

      /* Compute cut-off centers. */
      const Vector2 leftCutoff = invTimeHorizonObst * (obstacle1->point_ - position_);
      const Vector2 rightCutoff = invTimeHorizonObst * (obstacle2->point_ - position_);
      const Vector2 cutoffVec = rightCutoff - leftCutoff;

      /* Project current velocity on velocity obstacle. */
      
      /* Check if current velocity is projected on cutoff circles. */
      const float t = (obstacle1 == obstacle2 ? 0.5f : ((velocity_ - leftCutoff) * cutoffVec) / absSq(cutoffVec));
      const float tLeft = ((velocity_ - leftCutoff) * leftLegDirection);
      const float tRight = ((velocity_ - rightCutoff) * rightLegDirection);

      if ((t < 0.0f && tLeft < 0.0f) || (obstacle1 == obstacle2 && tLeft < 0.0f && tRight < 0.0f)) {
        /* Project on left cut-off circle. */
        const Vector2 unitW = normalize(velocity_ - leftCutoff);

        line.direction = Vector2(unitW.y(), -unitW.x());
        line.point = leftCutoff + radius_ * invTimeHorizonObst * unitW;
        orcaLines_.push_back(line);
        continue;
      } else if (t > 1.0f && tRight < 0.0f) {
        /* Project on right cut-off circle. */
        const Vector2 unitW = normalize(velocity_ - rightCutoff);

        line.direction = Vector2(unitW.y(), -unitW.x());
        line.point = rightCutoff + radius_ * invTimeHorizonObst * unitW;
        orcaLines_.push_back(line);
        continue;
      } 

      /* 
       * Project on left leg, right leg, or cut-off line, whichever is closest
       * to velocity.
       */
      const float distSqCutoff = ((t < 0.0f || t > 1.0f || obstacle1 == obstacle2) ? std::numeric_limits<float>::infinity() : absSq(velocity_ - (leftCutoff + t * cutoffVec)));
      const float distSqLeft = ((tLeft < 0.0f) ? std::numeric_limits<float>::infinity() : absSq(velocity_ - (leftCutoff + tLeft * leftLegDirection)));
      const float distSqRight = ((tRight < 0.0f) ? std::numeric_limits<float>::infinity() : absSq(velocity_ - (rightCutoff + tRight * rightLegDirection)));

      if (distSqCutoff <= distSqLeft && distSqCutoff <= distSqRight) {
        /* Project on cut-off line. */
        line.direction = -obstacle1->unitDir_;
        line.point = leftCutoff + radius_ * invTimeHorizonObst * Vector2(-line.direction.y(), line.direction.x());
        orcaLines_.push_back(line);
        continue;
      } else if (distSqLeft <= distSqRight) {
        /* Project on left leg. */
        if (isLeftLegForeign) {
          continue;
        } 
          
        line.direction = leftLegDirection;
        line.point = leftCutoff + radius_ * invTimeHorizonObst * Vector2(-line.direction.y(), line.direction.x());
        orcaLines_.push_back(line);
        continue;
      } else {
        /* Project on right leg. */
        if (isRightLegForeign) {
          continue;
        } 
        
        line.direction = -rightLegDirection;
        line.point = rightCutoff + radius_ * invTimeHorizonObst * Vector2(-line.direction.y(), line.direction.x());
        orcaLines_.push_back(line);
        continue;
      }
    }

    const size_t numObstLines = orcaLines_.size();

    const float invTimeHorizon = 1.0f / timeHorizon_;

    /* Create agent ORCA lines. */
    for (size_t i = 0; i < agentNeighbors_.size(); ++i) {
      const Agent* const other = agentNeighbors_[i].second;

      const Vector2 relativePosition = other->position_ - position_;
      const Vector2 relativeVelocity = velocity_ - other->velocity_;
      const float distSq = absSq(relativePosition);
      const float combinedRadius = radius_ + other->radius_;
      const float combinedRadiusSq = sqr(combinedRadius);

      Line line;
      Vector2 u;

      if (distSq > combinedRadiusSq) {
        /* No collision. */
        const Vector2 w = relativeVelocity - invTimeHorizon * relativePosition; 
        /* Vector from cutoff center to relative velocity. */
        const float wLengthSq = absSq(w);

        const float dotProduct1 = w * relativePosition;

        if (dotProduct1 < 0.0f && sqr(dotProduct1) > combinedRadiusSq * wLengthSq) {
          /* Project on cut-off circle. */
          const float wLength = std::sqrt(wLengthSq);
          const Vector2 unitW = w / wLength;

          line.direction = Vector2(unitW.y(), -unitW.x());
          u = (combinedRadius * invTimeHorizon - wLength) * unitW;
        } else {
          /* Project on legs. */
          const float leg = std::sqrt(distSq - combinedRadiusSq);

          if (det(relativePosition, w) > 0.0f) {
            /* Project on left leg. */
            line.direction = Vector2(relativePosition.x() * leg - relativePosition.y() * combinedRadius, relativePosition.x() * combinedRadius + relativePosition.y() * leg) / distSq;
          } else {
            /* Project on right leg. */
            line.direction = -Vector2(relativePosition.x() * leg + relativePosition.y() * combinedRadius, -relativePosition.x() * combinedRadius + relativePosition.y() * leg) / distSq;
          }

          const float dotProduct2 = relativeVelocity * line.direction;

          u = dotProduct2 * line.direction - relativeVelocity;
        }
      } else {
        /* Collision. Project on cut-off circle of time timeStep. */
        const float invTimeStep = 1.0f / sim_->timeStep_;

        /* Vector from cutoff center to relative velocity. */
        const Vector2 w = relativeVelocity - invTimeStep * relativePosition; 
                
        const float wLength = abs(w);
        const Vector2 unitW = w / wLength;

        line.direction = Vector2(unitW.y(), -unitW.x());
        u = (combinedRadius * invTimeStep - wLength) * unitW;
      }

      line.point = velocity_ + 0.5f * u;
      orcaLines_.push_back(line);
    }

    size_t lineFail = linearProgram2(orcaLines_, maxSpeed_, prefVelocity_, false, newVelocity_);

    if (lineFail < orcaLines_.size()) {
      linearProgram3(orcaLines_, numObstLines, lineFail, maxSpeed_, newVelocity_);
    }
  }

  void Agent::insertAgentNeighbor(const Agent* agent, float& rangeSq)
  {
    if (this != agent) {
      const float distSq = absSq(position_ - agent->position_);

      if (distSq < rangeSq) {
        if (agentNeighbors_.size() < maxNeighbors_) {
          agentNeighbors_.push_back(std::make_pair(distSq,agent));
        }
        size_t i = agentNeighbors_.size() - 1;
        while (i != 0 && distSq < agentNeighbors_[i-1].first) {
          agentNeighbors_[i] = agentNeighbors_[i-1];
          --i;
        }
        agentNeighbors_[i] = std::make_pair(distSq, agent);

        if (agentNeighbors_.size() == maxNeighbors_) {
          rangeSq = agentNeighbors_.back().first;
        }
      }
    }
  }

  void Agent::insertObstacleNeighbor(const Obstacle* obstacle, float rangeSq)
  {
    const Obstacle* const nextObstacle = obstacle->nextObstacle;

    const float distSq = distSqPointLineSegment(obstacle->point_, nextObstacle->point_, position_);

    if (distSq < rangeSq) {
      obstacleNeighbors_.push_back(std::make_pair(distSq,obstacle));
      
      size_t i = obstacleNeighbors_.size() - 1;
      while (i != 0 && distSq < obstacleNeighbors_[i-1].first) {
        obstacleNeighbors_[i] = obstacleNeighbors_[i-1];
        --i;
      }
      obstacleNeighbors_[i] = std::make_pair(distSq, obstacle);
    }
  }

  void Agent::update()
  {
    velocity_ = newVelocity_;
    position_ += velocity_ * sim_->timeStep_;
  }

  bool linearProgram1(const std::vector<Line>& lines, size_t lineNo, float radius, const Vector2& optVelocity, bool directionOpt, Vector2& result)
  {
    const float dotProduct = lines[lineNo].point * lines[lineNo].direction;
    const float discriminant = sqr(dotProduct) + sqr(radius) - absSq(lines[lineNo].point);
    
    if (discriminant < 0.0f) {
      /* Max speed circle fully invalidates line lineNo. */
      return false;
    }
    
    const float sqrtDiscriminant = std::sqrt(discriminant);
    float tLeft = -dotProduct - sqrtDiscriminant;
    float tRight = -dotProduct + sqrtDiscriminant;
    
    for (size_t i = 0; i < lineNo; ++i) {
      const float denominator = det(lines[lineNo].direction, lines[i].direction);
      const float numerator = det(lines[i].direction, lines[lineNo].point - lines[i].point);

      if (std::fabs(denominator) <= RVO_EPSILON) {
        /* Lines lineNo and i are (almost) parallel. */
        if (numerator < 0.0f) {
          return false;
        } else {
          continue;
        }
      }

      const float t = numerator / denominator;

      if (denominator >= 0.0f) {
        /* Line i bounds line lineNo on the right. */
        tRight = std::min(tRight, t);
      } else {
        /* Line i bounds line lineNo on the left. */
        tLeft = std::max(tLeft, t);
      }

      if (tLeft > tRight) {
        return false;
      }
    }

    if (directionOpt) {
      /* Optimize direction. */
      if (optVelocity * lines[lineNo].direction > 0.0f) {
        /* Take right extreme. */
        result = lines[lineNo].point + tRight * lines[lineNo].direction;
      } else {
        /* Take left extreme. */
        result = lines[lineNo].point + tLeft * lines[lineNo].direction;
      }
    } else {
      /* Optimize closest point. */
      const float t = lines[lineNo].direction * (optVelocity - lines[lineNo].point);

      if (t < tLeft) {
        result = lines[lineNo].point + tLeft * lines[lineNo].direction;
      } else if (t > tRight) {
        result = lines[lineNo].point + tRight * lines[lineNo].direction;
      } else {
        result = lines[lineNo].point + t * lines[lineNo].direction;
      }
    }

    return true;
  }

  size_t linearProgram2(const std::vector<Line>& lines, float radius, const Vector2& optVelocity, bool directionOpt, Vector2& result)
  {
    if (directionOpt) {
      /* 
       * Optimize direction. Note that the optimization velocity is of unit
       * length in this case.
       */
      result = optVelocity * radius;
    } else if (absSq(optVelocity) > sqr(radius)) {
      /* Optimize closest point and outside circle. */
      result = normalize(optVelocity) * radius;
    } else {
      /* Optimize closest point and inside circle. */
      result = optVelocity;
    }

    for (size_t i = 0; i < lines.size(); ++i) {
      if (det(lines[i].direction, lines[i].point - result) > 0.0f) {
        /* Result does not satisfy constraint i. Compute new optimal result. */
        const Vector2 tempResult = result;
        if (!linearProgram1(lines, i, radius, optVelocity, directionOpt, result)) {
          result = tempResult;
          return i;
        }
      }
    }

    return lines.size();
  }

  void linearProgram3(const std::vector<Line>& lines, size_t numObstLines, size_t beginLine, float radius, Vector2& result)
  {
    float distance = 0.0f;

    for (size_t i = beginLine; i < lines.size(); ++i) {
      if (det(lines[i].direction, lines[i].point - result) > distance) {
        /* Result does not satisfy constraint of line i. */
        std::vector<Line> projLines(lines.begin(), lines.begin() + numObstLines);

        for (size_t j = numObstLines; j < i; ++j) {
          Line line;

          float determinant = det(lines[i].direction, lines[j].direction);

          if (std::fabs(determinant) <= RVO_EPSILON) {
            /* Line i and line j are parallel. */
            if (lines[i].direction * lines[j].direction > 0.0f) {
              /* Line i and line j point in the same direction. */
              continue;
            } else {
              /* Line i and line j point in opposite direction. */
              line.point = 0.5f * (lines[i].point + lines[j].point);
            }
          } else {
            line.point = lines[i].point + (det(lines[j].direction, lines[i].point - lines[j].point) / determinant) * lines[i].direction;
          }

          line.direction = normalize(lines[j].direction - lines[i].direction);
          projLines.push_back(line);
        }

        const Vector2 tempResult = result;
        if (linearProgram2(projLines, radius, Vector2(-lines[i].direction.y(), lines[i].direction.x()), true, result) < projLines.size()) {
          /* This should in principle not happen.  The result is by definition
           * already in the feasible region of this linear program. If it fails,
           * it is due to small floating point error, and the current result is
           * kept.
           */
          result = tempResult;
        }

        distance = det(lines[i].direction, lines[i].point - result);
      }
    }
  }
}
