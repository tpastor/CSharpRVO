// RVO3D.h
#pragma once

#include "RVOSimulator.h"

using Microsoft::Xna::Framework::Vector3;
using namespace System;

namespace RVO3D {

	public ref class RVOSimulator
	{
			private:
				RVO::RVOSimulator* _sim;
			public:
				RVOSimulator();	
				RVOSimulator(float timeStep, float neighborDist, size_t maxNeighbors, float timeHorizon, float radius, float maxSpeed,Vector3 velocity);
				~RVOSimulator();

				int addAgent(Vector3 position);
				int addAgent(Vector3 position, float neighborDist, int maxNeighbors, float timeHorizon, float radius, float maxSpeed, Vector3 velocity );
				void doStep();

				int getAgentAgentNeighbor(int agentNo, int neighborNo) ;
				int getAgentMaxNeighbors(int agentNo) ;
				float getAgentMaxSpeed(int agentNo) ;

				float getAgentNeighborDist(int agentNo) ;
				int getAgentNumAgentNeighbors(int agentNo) ;
				int getAgentNumORCAPlanes(int agentNo) ;

				Vector3  getAgentPosition(int agentNo) ;
				Vector3  getAgentPrefVelocity(int agentNo) ;

				void getAgentPositions(array<int>^ agentNos, array<Vector3>^ positions) ;
				void getAgentPrefVelocities(array<int>^ agentNos, array<Vector3>^ prefVelocities) ;

				float getAgentRadius(int agentNo) ;
				float getAgentTimeHorizon(int agentNo) ;
				Vector3 getAgentVelocity(int agentNo) ;
				float getGlobalTime() ;
				int getNumAgents() ;
				float getTimeStep() ;
				void removeAgent(int agentNo);
				void setAgentDefaults(float neighborDist, int maxNeighbors, float timeHorizon, float radius, float maxSpeed, Vector3 velocity);
				void setAgentMaxNeighbors(int agentNo, int maxNeighbors);
				void setAgentMaxSpeed(int agentNo, float maxSpeed);
				void setAgentNeighborDist(int agentNo, float neighborDist);
				void setAgentPosition(int agentNo,  Vector3 position);
				void setAgentPrefVelocity(int agentNo,  Vector3 prefVelocity);
				void setAgentPrefVelocity(array<int>^ agentNo,  array<Vector3>^ prefVelocity);

				void setAgentRadius(int agentNo, float radius);
				void setAgentTimeHorizon(int agentNo, float timeHorizon);
				void setAgentVelocity(int agentNo,  Vector3 velocity);
				void setAgentVelocity(array<int>^ agentNo,  array<Vector3>^ velocity);
				void setTimeStep(float timeStep);				
				
	};
}
