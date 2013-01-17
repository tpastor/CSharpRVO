// RVO2DWrapper.h

#pragma once

#include "RVOSimulator.h"

using namespace System;

namespace RVO2D {

	public ref class RVOSimulator
	{
		private:
				RVO::RVOSimulator* _sim;
			public:
				RVOSimulator();	
				RVOSimulator(float timeStep, float neighborDist, int maxNeighbors, float timeHorizon,float obsHorizon ,float radius, float maxSpeed,Microsoft::Xna::Framework::Vector2 velocity);
				~RVOSimulator();

				int addAgent(Microsoft::Xna::Framework::Vector2 position);
				int addAgent(Microsoft::Xna::Framework::Vector2 position, float neighborDist, int maxNeighbors, float timeHorizon,float timeHorizonObst, float radius, float maxSpeed, Microsoft::Xna::Framework::Vector2 velocity );
				void doStep();

				int getAgentAgentNeighbor(int agentNo, int neighborNo) ;
				int getAgentMaxNeighbors(int agentNo) ;
				float getAgentMaxSpeed(int agentNo) ;

				float getAgentNeighborDist(int agentNo) ;
				int getAgentNumAgentNeighbors(int agentNo) ;

				Microsoft::Xna::Framework::Vector2  getAgentPosition(int agentNo) ;
				Microsoft::Xna::Framework::Vector2  getAgentPrefVelocity(int agentNo) ;

				void getAgentPositions(array<int>^ agentNos, array<Microsoft::Xna::Framework::Vector2>^ positions) ;
				void getAgentPrefVelocities(array<int>^ agentNos, array<Microsoft::Xna::Framework::Vector2>^ prefVelocities) ;

				float getAgentRadius(int agentNo) ;
				float getAgentTimeHorizon(int agentNo) ;
				Microsoft::Xna::Framework::Vector2 getAgentVelocity(int agentNo) ;
				float getGlobalTime() ;
				int getNumAgents() ;
				float getTimeStep() ;
				void setAgentDefaults(float neighborDist, int maxNeighbors, float timeHorizon,float obsHorizon, float radius, float maxSpeed, Microsoft::Xna::Framework::Vector2 velocity);
				void setAgentMaxNeighbors(int agentNo, int maxNeighbors);
				void setAgentMaxSpeed(int agentNo, float maxSpeed);
				void setAgentNeighborDist(int agentNo, float neighborDist);
				void setAgentPosition(int agentNo,  Microsoft::Xna::Framework::Vector2 position);
				void setAgentPrefVelocity(int agentNo,  Microsoft::Xna::Framework::Vector2 prefVelocity);
				void setAgentPrefVelocity(array<int>^ agentNo,  array<Microsoft::Xna::Framework::Vector2>^ prefVelocity);

				void setAgentRadius(int agentNo, float radius);
				void setAgentTimeHorizon(int agentNo, float timeHorizon);
				void setAgentVelocity(int agentNo,  Microsoft::Xna::Framework::Vector2 velocity);
				void setAgentVelocity(array<int>^ agentNo,  array<Microsoft::Xna::Framework::Vector2>^ velocity);
				void setTimeStep(float timeStep);	


				
				int addObstacle(array<Microsoft::Xna::Framework::Vector2>^ vertices);
				int addObstacle(System::Collections::Generic::List<Microsoft::Xna::Framework::Vector2>^ vertices);

				void processObstacles();
				bool queryVisibility(Microsoft::Xna::Framework::Vector2 point1, Microsoft::Xna::Framework::Vector2 point2, float radius) ;
				float getAgentTimeHorizonObst(int agentNo) ;
				void setAgentTimeHorizonObst(int agentNo, float timeHorizonObst);
				
	};
}
