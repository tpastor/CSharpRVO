/*
 *  Agent.cpp
 *  RVO2-3D Library.
 *
 *  Copyright (C) 2008-11 University of North Carolina at Chapel Hill.
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

#include "API.h"
#include "Agent.h"

#include <cmath>

#include "Definitions.h"
#include "KdTree.h"

namespace RVO
{
/*!
 *  @brief		A sufficiently small positive number.
 */
static const float RVO_EPSILON = 0.00001f;

/*!
 *  @brief		Defines a directed line.
 */
struct Line
{
	/*!
	 *  @brief		A point on the directed line.
	 */
	Vector3 point;

	/*!
	 *  @brief		The direction of the directed line.
	 */
	Vector3 direction;
};

/*!
 *  @brief		Solves a one-dimensional linear program on a specified line subject to linear constraints defined by planes and a spherical constraint.
 *  @param		planes				Planes defining the linear constraints.
 *  @param		planeNo				The plane on which the line lies.
 *  @param		line				The line on which the 1-d linear program is solved
 *  @param		radius				The radius of the spherical constraint.
 *  @param		optVelocity			The optimization velocity.
 *  @param		directionOpt		True if the direction should be optimized.
 *  @param		result				A reference to the result of the linear program.
 *  @returns	True if successful.
 */
bool linearProgram1(const std::vector<Plane>& planes, size_t planeNo, const Line& line, float radius, const Vector3& optVelocity, bool directionOpt, Vector3& result);

/*!
 *  @brief      Solves a two-dimensional linear program on a specified plane subject to linear constraints defined by planes and a spherical constraint.
 *  @param      planes				Planes defining the linear constraints.
 *  @param      planeNo				The plane on which the 2-d linear program is solved
 *  @param      radius				The radius of the spherical constraint.
 *  @param      optVelocity			The optimization velocity.
 *  @param      directionOpt		True if the direction should be optimized.
 *  @param      result				A reference to the result of the linear program.
 *  @returns    True if successful.
 */
bool linearProgram2(const std::vector<Plane>& planes, size_t planeNo, float radius, const Vector3& optVelocity, bool directionOpt, Vector3& result);


/*!
 *  @brief      Solves a three-dimensional linear program subject to linear constraints defined by planes and a spherical constraint.
 *  @param      planes				Planes defining the linear constraints.
 *  @param      radius				The radius of the spherical constraint.
 *  @param      optVelocity			The optimization velocity.
 *  @param      directionOpt		True if the direction should be optimized.
 *  @param      result				A reference to the result of the linear program.
 *  @returns    The number of the plane it fails on, and the number of planes if successful.
 */
size_t linearProgram3(const std::vector<Plane>& planes, float radius, const Vector3& optVelocity, bool directionOpt, Vector3& result);

/*!
 *  @brief      Solves a four-dimensional linear program subject to linear constraints defined by planes and a spherical constraint.
 *  @param      planes			Planes defining the linear constraints.
 *  @param      beginLine		The plane on which the 3-d linear program failed.
 *  @param      radius			The radius of the spherical constraint.
 *  @param      result			A reference to the result of the linear program.
 */
void linearProgram4(const std::vector<Plane>& planes, size_t beginPlane, float radius, Vector3& result);

Agent::Agent(RVOSimulator* sim) : agentNeighbors_(), id_(0), maxNeighbors_(0), maxSpeed_(0.0f), neighborDist_(0.0f), newVelocity_(), orcaPlanes_(), position_(), prefVelocity_(), radius_(0.0f), sim_(sim), timeHorizon_(0.0f), velocity_()
{
}

void Agent::computeNeighbors()
{
	agentNeighbors_.clear();

	if (maxNeighbors_ > 0) {
		float rangeSq = sqr(neighborDist_);
		sim_->kdTree_->computeAgentNeighbors(this, rangeSq);
	}
}

/* Search for the best new velocity. */
void Agent::computeNewVelocity()
{
	orcaPlanes_.clear();
	const float invTimeHorizon = 1.0f / timeHorizon_;

	/* Create agent ORCA planes. */
	for (size_t i = 0; i < agentNeighbors_.size(); ++i) {
		const Agent* const other = agentNeighbors_[i].second;

		const Vector3 relativePosition = other->position_ - position_;
		const Vector3 relativeVelocity = velocity_ - other->velocity_;
		const float distSq = absSq(relativePosition);
		const float combinedRadius = radius_ + other->radius_;
		const float combinedRadiusSq = sqr(combinedRadius);

		Plane plane;
		Vector3 u;

		if (distSq > combinedRadiusSq) {
			/* No collision. */
			const Vector3 w = relativeVelocity - invTimeHorizon * relativePosition;
			/* Vector from cutoff center to relative velocity. */
			const float wLengthSq = absSq(w);

			const float dotProduct1 = w * relativePosition;

			if (dotProduct1 < 0.0f && sqr(dotProduct1) > combinedRadiusSq * wLengthSq) {
				/* Project on cut-off circle. */
				const float wLength = std::sqrt(wLengthSq);
				const Vector3 unitW = w / wLength;

				plane.normal = unitW;
				u = (combinedRadius * invTimeHorizon - wLength) * unitW;
			}
			else {
				/* Project on cone. */
				const float A = distSq;
				const float B = relativePosition * relativeVelocity;
				const float C = absSq(relativeVelocity) - absSq(cross(relativePosition, relativeVelocity)) / (distSq - combinedRadiusSq);

				const float t = (B + std::sqrt(sqr(B) - A * C)) / A;
				const Vector3 w = relativeVelocity - t * relativePosition;
				const float wLength = abs(w);
				const Vector3 unitW = w / wLength;

				plane.normal = unitW;
				u = (combinedRadius * t - wLength) * unitW;
			}
		}
		else {
			/* Collision. */
			const float invTimeStep = 1.0f / sim_->timeStep_;

			const Vector3 w = relativeVelocity - invTimeStep * relativePosition;
			const float wLength = abs(w);
			const Vector3 unitW = w / wLength;

			plane.normal = unitW;
			u = (combinedRadius * invTimeStep - wLength) * unitW;
		}

		plane.point = velocity_ + 0.5f * u;
		orcaPlanes_.push_back(plane);
	}

	const size_t planeFail = linearProgram3(orcaPlanes_, maxSpeed_, prefVelocity_, false, newVelocity_);

	if (planeFail < orcaPlanes_.size()) {
		linearProgram4(orcaPlanes_, planeFail, maxSpeed_, newVelocity_);
	}
}

void Agent::insertAgentNeighbor(const Agent* agent, float& rangeSq)
{
	if (this != agent) {
		const float distSq = absSq(position_ - agent->position_);

		if (distSq < rangeSq) {
			if (agentNeighbors_.size() < maxNeighbors_) {
				agentNeighbors_.push_back(std::make_pair(distSq, agent));
			}

			size_t i = agentNeighbors_.size() - 1;

			while (i != 0 && distSq < agentNeighbors_[i - 1].first) {
				agentNeighbors_[i] = agentNeighbors_[i - 1];
				--i;
			}

			agentNeighbors_[i] = std::make_pair(distSq, agent);

			if (agentNeighbors_.size() == maxNeighbors_) {
				rangeSq = agentNeighbors_.back().first;
			}
		}
	}
}

void Agent::update()
{
	velocity_ = newVelocity_;
	position_ += velocity_ * sim_->timeStep_;
}

bool linearProgram1(const std::vector<Plane>& planes, size_t planeNo, const Line& line, float radius, const Vector3& optVelocity, bool directionOpt, Vector3& result)
{
	const float dotProduct = line.point * line.direction;
	const float discriminant = sqr(dotProduct) + sqr(radius) - absSq(line.point);

	if (discriminant < 0.0f) {
		/* Max speed sphere fully invalidates line. */
		return false;
	}

	const float sqrtDiscriminant = std::sqrt(discriminant);

	float tLeft = -dotProduct - sqrtDiscriminant;

	float tRight = -dotProduct + sqrtDiscriminant;

	for (size_t i = 0; i < planeNo; ++i) {
		const float numerator = (planes[i].point - line.point) * planes[i].normal;
		const float denominator = line.direction * planes[i].normal;

		if (sqr(denominator) <= RVO_EPSILON) {
			/* Lines line is (almost) parallel to plane i. */
			if (numerator > 0.0f) {
				return false;
			}
			else {
				continue;
			}
		}

		const float t = numerator / denominator;

		if (denominator >= 0.0f) {
			/* Plane i bounds line on the left. */
			tLeft = std::max(tLeft, t);
		}
		else {
			/* Plane i bounds line on the right. */
			tRight = std::min(tRight, t);
		}

		if (tLeft > tRight) {
			return false;
		}
	}

	if (directionOpt) {
		/* Optimize direction. */
		if (optVelocity * line.direction > 0.0f) {
			/* Take right extreme. */
			result = line.point + tRight * line.direction;
		}
		else {
			/* Take left extreme. */
			result = line.point + tLeft * line.direction;
		}
	}
	else {
		/* Optimize closest point. */
		const float t = line.direction * (optVelocity - line.point);

		if (t < tLeft) {
			result = line.point + tLeft * line.direction;
		}
		else if (t > tRight) {
			result = line.point + tRight * line.direction;
		}
		else {
			result = line.point + t * line.direction;
		}
	}

	return true;
}

bool linearProgram2(const std::vector<Plane>& planes, size_t planeNo, float radius, const Vector3& optVelocity, bool directionOpt, Vector3& result)
{
	const float planeDist = planes[planeNo].point * planes[planeNo].normal;
	const float planeDistSq = sqr(planeDist);
	const float radiusSq = sqr(radius);

	if (planeDistSq > radiusSq) {
		/* Max speed sphere fully invalidates plane planeNo. */
		return false;
	}

	const float planeRadiusSq = radiusSq - planeDistSq;

	const Vector3 planeCenter = planeDist * planes[planeNo].normal;

	if (directionOpt) {
		/* Project direction optVelocity on plane planeNo. */
		const Vector3 planeOptVelocity = optVelocity - (optVelocity * planes[planeNo].normal) * planes[planeNo].normal;
		const float planeOptVelocityLengthSq = absSq(planeOptVelocity);

		if (planeOptVelocityLengthSq <= RVO_EPSILON) {
			result = planeCenter;
		}
		else {
			result = planeCenter + std::sqrt(planeRadiusSq / planeOptVelocityLengthSq) * planeOptVelocity;
		}
	}
	else {
		/* Project point optVelocity on plane planeNo. */
		result = optVelocity + ((planes[planeNo].point - optVelocity) * planes[planeNo].normal) * planes[planeNo].normal;

		/* If outside planeCircle, project on planeCircle. */
		if (absSq(result) > radiusSq) {
			const Vector3 planeResult = result - planeCenter;
			const float planeResultLengthSq = absSq(planeResult);
			result = planeCenter + std::sqrt(planeRadiusSq / planeResultLengthSq) * planeResult;
		}
	}

	for (size_t i = 0; i < planeNo; ++i) {
		if (planes[i].normal * (planes[i].point - result) > 0.0f) {
			/* Result does not satisfy constraint i. Compute new optimal result. */

			/* Compute intersection line of plane i and plane planeNo. */
			Vector3 crossProduct = cross(planes[i].normal, planes[planeNo].normal);

			if (absSq(crossProduct) <= RVO_EPSILON) {
				/* Planes planeNo and i are (almost) parallel, and plane i fully invalidates plane planeNo. */
				return false;
			}

			Line line;
			line.direction = normalize(crossProduct);
			const Vector3 lineNormal = cross(line.direction, planes[planeNo].normal);
			line.point = planes[planeNo].point + (((planes[i].point - planes[planeNo].point) * planes[i].normal) / (lineNormal * planes[i].normal)) * lineNormal;

			if (!linearProgram1(planes, i, line, radius, optVelocity, directionOpt, result)) {
				return false;
			}
		}
	}

	return true;
}

size_t linearProgram3(const std::vector<Plane>& planes, float radius, const Vector3& optVelocity, bool directionOpt, Vector3& result)
{
	if (directionOpt) {
		/* Optimize direction. Note that the optimization velocity is of unit length in this case. */
		result = optVelocity * radius;
	}
	else if (absSq(optVelocity) > sqr(radius)) {
		/* Optimize closest point and outside circle. */
		result = normalize(optVelocity) * radius;
	}
	else {
		/* Optimize closest point and inside circle. */
		result = optVelocity;
	}

	for (size_t i = 0; i < planes.size(); ++i) {
		if (planes[i].normal * (planes[i].point - result) > 0.0f) {
			/* Result does not satisfy constraint i. Compute new optimal result. */
			const Vector3 tempResult = result;

			if (!linearProgram2(planes, i, radius, optVelocity, directionOpt, result)) {
				result = tempResult;
				return i;
			}
		}
	}

	return planes.size();
}

void linearProgram4(const std::vector<Plane>& planes, size_t beginPlane, float radius, Vector3& result)
{
	float distance = 0.0f;

	for (size_t i = beginPlane; i < planes.size(); ++i) {
		if (planes[i].normal * (planes[i].point - result) > distance) {
			/* Result does not satisfy constraint of plane i. */
			std::vector<Plane> projPlanes;

			for (size_t j = 0; j < i; ++j) {
				Plane plane;

				const Vector3 crossProduct = cross(planes[j].normal, planes[i].normal);

				if (absSq(crossProduct) <= RVO_EPSILON) {
					/* Plane i and plane j are (almost) parallel. */
					if (planes[i].normal * planes[j].normal > 0.0f) {
						/* Plane i and plane j point in the same direction. */
						continue;
					}
					else {
						/* Plane i and plane j point in opposite direction. */
						plane.point = 0.5f * (planes[i].point + planes[j].point);
					}
				}
				else {
					/* Plane.point is point on line of intersection between plane i and plane j. */
					const Vector3 lineNormal = cross(crossProduct, planes[i].normal);
					plane.point = planes[i].point + (((planes[j].point - planes[i].point) * planes[j].normal) / (lineNormal * planes[j].normal)) * lineNormal;
				}

				plane.normal = normalize(planes[j].normal - planes[i].normal);
				projPlanes.push_back(plane);
			}

			const Vector3 tempResult = result;

			if (linearProgram3(projPlanes, radius, planes[i].normal, true, result) < projPlanes.size()) {
				/* This should in principle not happen.  The result is by definition already in the feasible region of this linear program. If it fails, it is due to small floating point error, and the current result is kept. */
				result = tempResult;
			}

			distance = planes[i].normal * (planes[i].point - result);
		}
	}
}
}
