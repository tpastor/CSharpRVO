// This is the main DLL file.

#include <vector>

#include "stdafx.h"
#include "RVO2DWrapper.h"

using namespace RVO2D;

RVOSimulator::RVOSimulator()
{	
	_sim = new RVO::RVOSimulator() ;
}

RVOSimulator::RVOSimulator(float timeStep, float neighborDist, int maxNeighbors, float timeHorizon,float obsHorizon ,float radius, float maxSpeed,Microsoft::Xna::Framework::Vector2 velocity)
{
	RVO::Vector2 vec = RVO::Vector2(velocity.X,velocity.Y);	
	_sim = new RVO::RVOSimulator(timeStep,neighborDist,maxNeighbors,timeHorizon,obsHorizon,radius,maxSpeed,vec) ;
	
}

int RVOSimulator::addAgent(Microsoft::Xna::Framework::Vector2 position)
{
		 RVO::Vector2 pos = RVO::Vector2(position.X,position.Y);	
		 return _sim->addAgent(pos);
}


int RVOSimulator::addAgent(Microsoft::Xna::Framework::Vector2 position, float neighborDist, int maxNeighbors, float timeHorizon,float timeHorizonObst, float radius, float maxSpeed, Microsoft::Xna::Framework::Vector2 velocity )
{
	RVO::Vector2 pos = RVO::Vector2(position.X,position.Y);	
	RVO::Vector2 vel = RVO::Vector2(velocity.X,velocity.Y);		
	return _sim->addAgent(pos,neighborDist, maxNeighbors, timeHorizon, timeHorizonObst,radius, maxSpeed, vel); 
}

void RVOSimulator::doStep()
{
	_sim->doStep();
}

RVOSimulator::~RVOSimulator()
{
	delete _sim;
}


int RVOSimulator::getAgentAgentNeighbor(int agentNo, int neighborNo)
{
	return _sim->getAgentAgentNeighbor(agentNo, neighborNo);
}
int RVOSimulator::getAgentMaxNeighbors(int agentNo)
{
	return _sim->getAgentMaxNeighbors(agentNo);
}
float RVOSimulator::getAgentMaxSpeed(int agentNo)
{
	return _sim->getAgentMaxSpeed(agentNo);
}

float RVOSimulator::getAgentNeighborDist(int agentNo) 
{
	return _sim->getAgentNeighborDist(agentNo);
}
int RVOSimulator::getAgentNumAgentNeighbors(int agentNo) 
{
	return _sim->getAgentNumAgentNeighbors(agentNo);
}

void RVOSimulator::getAgentPositions(array<int>^ agentNo, array<Microsoft::Xna::Framework::Vector2>^ positions) 
{
	positions = gcnew array<Microsoft::Xna::Framework::Vector2>(agentNo->Length);
	for(int i =0 ; i < agentNo->Length; i++)
	{
		RVO::Vector2 v = _sim->getAgentPosition(agentNo[i]);
		positions[i] = Microsoft::Xna::Framework::Vector2( v.x(),v.y());		
	}
}

void RVOSimulator::getAgentPrefVelocities(array<int>^ agentNo,array<Microsoft::Xna::Framework::Vector2>^ prefVelocities) 
{
	prefVelocities = gcnew array<Microsoft::Xna::Framework::Vector2>(agentNo->Length);
	for(int i =0 ; i < agentNo->Length; i++)
	{
		RVO::Vector2 v = _sim->getAgentPrefVelocity(agentNo[i]);
		prefVelocities[i] = Microsoft::Xna::Framework::Vector2( v.x(),v.y());		
	}
}

Microsoft::Xna::Framework::Vector2  RVOSimulator::getAgentPosition(int agentNo) 
{
	 RVO::Vector2 v = _sim->getAgentPosition(agentNo);
	 Microsoft::Xna::Framework::Vector2 vec = Microsoft::Xna::Framework::Vector2( v.x(),v.y());
	 return vec;
}

Microsoft::Xna::Framework::Vector2  RVOSimulator::getAgentPrefVelocity(int agentNo) 
{
	 RVO::Vector2 v = _sim->getAgentPrefVelocity(agentNo);
	 Microsoft::Xna::Framework::Vector2 vec = Microsoft::Xna::Framework::Vector2( v.x(),v.y());
	 return vec;
}

float RVOSimulator::getAgentRadius(int agentNo) 
{
	return _sim->getAgentRadius(agentNo);
}


float RVOSimulator::getAgentTimeHorizon(int agentNo) 
{
	return _sim->getAgentTimeHorizon(agentNo);
}

Microsoft::Xna::Framework::Vector2 RVOSimulator::getAgentVelocity(int agentNo) 
{
	 RVO::Vector2 v = _sim->getAgentVelocity(agentNo);
	 Microsoft::Xna::Framework::Vector2 vec = Microsoft::Xna::Framework::Vector2( v.x(),v.y());
	 return vec;
}
float RVOSimulator::getGlobalTime() 
{
	return _sim->getGlobalTime();
}
int RVOSimulator::getNumAgents() 
{
	return _sim->getNumAgents();
}

float RVOSimulator::getTimeStep() 
{
	return _sim->getTimeStep();
}
void RVOSimulator::setAgentDefaults(float neighborDist, int maxNeighbors, float timeHorizon,float obsHorizon, float radius, float maxSpeed, Microsoft::Xna::Framework::Vector2 velocity)
{
	RVO::Vector2 vel= RVO::Vector2(velocity.X,velocity.Y);	
	_sim->setAgentDefaults(neighborDist, maxNeighbors, timeHorizon,obsHorizon ,radius, maxSpeed, vel);
}
void RVOSimulator::setAgentMaxNeighbors(int agentNo, int maxNeighbors)
{
	_sim->setAgentMaxNeighbors(agentNo,maxNeighbors);
}
void RVOSimulator::setAgentMaxSpeed(int agentNo, float maxSpeed)
{
	_sim->setAgentMaxSpeed(agentNo,maxSpeed);
}
void RVOSimulator::setAgentNeighborDist(int agentNo, float neighborDist)
{
	_sim->setAgentNeighborDist(agentNo,neighborDist);
}
void RVOSimulator::setAgentPosition(int agentNo,  Microsoft::Xna::Framework::Vector2 position)
{
	RVO::Vector2 pos= RVO::Vector2(position.X,position.Y);	
	_sim->setAgentPosition(agentNo,pos);
}
void RVOSimulator::setAgentPrefVelocity(int agentNo,  Microsoft::Xna::Framework::Vector2 velocity)
{
	RVO::Vector2 vel= RVO::Vector2(velocity.X,velocity.Y);	
	_sim->setAgentPrefVelocity(agentNo,vel);
}

void RVOSimulator::setAgentPrefVelocity(array<int>^ agentNo,  array<Microsoft::Xna::Framework::Vector2>^ prefVelocity)
{
	for(int i =0 ; i < agentNo->Length; i++)
	{
		RVO::Vector2 vel= RVO::Vector2(prefVelocity[i].X,prefVelocity[i].Y);	
		_sim->setAgentPrefVelocity(agentNo[i],vel);
	}
}

void RVOSimulator::setAgentRadius(int agentNo, float radius)
{
	_sim->setAgentRadius(agentNo,radius);
}
void RVOSimulator::setAgentTimeHorizon(int agentNo, float timeHorizon)
{
	_sim->setAgentTimeHorizon(agentNo,timeHorizon);
}
void RVOSimulator::setAgentVelocity(int agentNo,  Microsoft::Xna::Framework::Vector2 velocity)
{
	RVO::Vector2 vel= RVO::Vector2(velocity.X,velocity.Y);	
	_sim->setAgentVelocity(agentNo,vel);
}
void RVOSimulator::setTimeStep(float timeStep)
{
	_sim->setTimeStep(timeStep);
}

void RVOSimulator::setAgentVelocity(array<int>^ agentNo,  array<Microsoft::Xna::Framework::Vector2>^ velocity)
{
	for(int i =0 ; i < agentNo->Length; i++)
	{
		RVO::Vector2 vel= RVO::Vector2(velocity[i].X,velocity[i].Y);	
		_sim->setAgentVelocity(agentNo[i],vel);
	}
}

int RVOSimulator::addObstacle(System::Collections::Generic::List<Microsoft::Xna::Framework::Vector2>^ vertices)
{
	std::vector<RVO::Vector2> vert;	
	for(int i =0 ; i < vertices->Count; i++)
	{		
		vert.push_back(RVO::Vector2(vertices[i].X,vertices[i].Y));
	}
	return _sim->addObstacle(vert);	
}

int RVOSimulator::addObstacle(array<Microsoft::Xna::Framework::Vector2>^ vertices)
{
	std::vector<RVO::Vector2> vert;	
	for(int i =0 ; i < vertices->Length; i++)
	{		
		vert.push_back(RVO::Vector2(vertices[i].X,vertices[i].Y));
	}
	return _sim->addObstacle(vert);

}
void RVOSimulator::processObstacles()
{
	_sim->processObstacles();
}
bool RVOSimulator::queryVisibility(Microsoft::Xna::Framework::Vector2 point1, Microsoft::Xna::Framework::Vector2 point2, float radius) 
{
	RVO::Vector2 p1= RVO::Vector2(point1.X,point1.Y);	
	RVO::Vector2 p2= RVO::Vector2(point2.X,point2.Y);	
	return _sim->queryVisibility(p1,p2,radius) ;
}
float RVOSimulator::getAgentTimeHorizonObst(int agentNo) 
{
	return _sim->getAgentTimeHorizonObst(agentNo) ;
}
void RVOSimulator::setAgentTimeHorizonObst(int agentNo, float timeHorizonObst)
{
	_sim->setAgentTimeHorizonObst(agentNo,timeHorizonObst) ;
}