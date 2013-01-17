// This is the main DLL file.
		
#include "stdafx.h"
#include "RVO3D.h"

using Microsoft::Xna::Framework::Vector3;
using namespace RVO3D;

RVOSimulator::RVOSimulator()
{	
	_sim = new RVO::RVOSimulator() ;
}

RVOSimulator::RVOSimulator(float timeStep, float neighborDist, size_t maxNeighbors, float timeHorizon, float radius, float maxSpeed,Microsoft::Xna::Framework::Vector3 velocity)
{
	RVO::Vector3 vec = RVO::Vector3(velocity.X,velocity.Y,velocity.Z);	
	_sim = new RVO::RVOSimulator(timeStep,neighborDist,maxNeighbors,timeHorizon,radius,maxSpeed,vec) ;
}

int RVOSimulator::addAgent(Microsoft::Xna::Framework::Vector3 position)
{
		 RVO::Vector3 pos = RVO::Vector3(position.X,position.Y,position.Z);	
		 return _sim->addAgent(pos);
}


int RVOSimulator::addAgent(Microsoft::Xna::Framework::Vector3 position, float neighborDist, int maxNeighbors, float timeHorizon, float radius, float maxSpeed, Microsoft::Xna::Framework::Vector3 velocity )
{
	RVO::Vector3 pos = RVO::Vector3(position.X,position.Y,position.Z);	
	RVO::Vector3 vel = RVO::Vector3(velocity.X,velocity.Y,velocity.Z);	
	return _sim->addAgent(pos,neighborDist, maxNeighbors, timeHorizon, radius, maxSpeed, vel); 
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
int RVOSimulator::getAgentNumORCAPlanes(int agentNo) 
{
	return _sim->getAgentNumORCAPlanes(agentNo);
}

void RVOSimulator::getAgentPositions(array<int>^ agentNo, array<Vector3>^ positions) 
{
	positions = gcnew array<Vector3>(agentNo->Length);
	for(int i =0 ; i < agentNo->Length; i++)
	{
		RVO::Vector3 v = _sim->getAgentPosition(agentNo[i]);
		positions[i] = Microsoft::Xna::Framework::Vector3( v.x(),v.y(),v.z() );		
	}
}

void RVOSimulator::getAgentPrefVelocities(array<int>^ agentNo,array<Vector3>^ prefVelocities) 
{
	prefVelocities = gcnew array<Vector3>(agentNo->Length);
	for(int i =0 ; i < agentNo->Length; i++)
	{
		RVO::Vector3 v = _sim->getAgentPrefVelocity(agentNo[i]);
		prefVelocities[i] = Microsoft::Xna::Framework::Vector3( v.x(),v.y(),v.z() );		
	}
}

Microsoft::Xna::Framework::Vector3  RVOSimulator::getAgentPosition(int agentNo) 
{
	 RVO::Vector3 v = _sim->getAgentPosition(agentNo);
	 Microsoft::Xna::Framework::Vector3 vec = Microsoft::Xna::Framework::Vector3( v.x(),v.y(),v.z() );
	 return vec;
}

Microsoft::Xna::Framework::Vector3  RVOSimulator::getAgentPrefVelocity(int agentNo) 
{
	 RVO::Vector3 v = _sim->getAgentPrefVelocity(agentNo);
	 Microsoft::Xna::Framework::Vector3 vec = Microsoft::Xna::Framework::Vector3( v.x(),v.y(),v.z() );
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

Microsoft::Xna::Framework::Vector3 RVOSimulator::getAgentVelocity(int agentNo) 
{
	 RVO::Vector3 v = _sim->getAgentVelocity(agentNo);
	 Microsoft::Xna::Framework::Vector3 vec = Microsoft::Xna::Framework::Vector3( v.x(),v.y(),v.z() );
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
void RVOSimulator::removeAgent(int agentNo)
{
	_sim->removeAgent(agentNo);
}
void RVOSimulator::setAgentDefaults(float neighborDist, int maxNeighbors, float timeHorizon, float radius, float maxSpeed, Microsoft::Xna::Framework::Vector3 velocity)
{
	RVO::Vector3 vel= RVO::Vector3(velocity.X,velocity.Y,velocity.Z);	
	_sim->setAgentDefaults(neighborDist, maxNeighbors, timeHorizon, radius, maxSpeed, vel);
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
void RVOSimulator::setAgentPosition(int agentNo,  Microsoft::Xna::Framework::Vector3 position)
{
	RVO::Vector3 pos= RVO::Vector3(position.X,position.Y,position.Z);	
	_sim->setAgentPosition(agentNo,pos);
}
void RVOSimulator::setAgentPrefVelocity(int agentNo,  Microsoft::Xna::Framework::Vector3 velocity)
{
	RVO::Vector3 vel= RVO::Vector3(velocity.X,velocity.Y,velocity.Z);	
	_sim->setAgentPrefVelocity(agentNo,vel);
}

void RVOSimulator::setAgentPrefVelocity(array<int>^ agentNo,  array<Vector3>^ prefVelocity)
{
	for(int i =0 ; i < agentNo->Length; i++)
	{
		RVO::Vector3 vel= RVO::Vector3(prefVelocity[i].X,prefVelocity[i].Y,prefVelocity[i].Z);	
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
void RVOSimulator::setAgentVelocity(int agentNo,  Microsoft::Xna::Framework::Vector3 velocity)
{
	RVO::Vector3 vel= RVO::Vector3(velocity.X,velocity.Y,velocity.Z);	
	_sim->setAgentVelocity(agentNo,vel);
}
void RVOSimulator::setTimeStep(float timeStep)
{
	_sim->setTimeStep(timeStep);
}

void RVOSimulator::setAgentVelocity(array<int>^ agentNo,  array<Vector3>^ velocity)
{
	for(int i =0 ; i < agentNo->Length; i++)
	{
		RVO::Vector3 vel= RVO::Vector3(velocity[i].X,velocity[i].Y,velocity[i].Z);	
		_sim->setAgentVelocity(agentNo[i],vel);
	}
}