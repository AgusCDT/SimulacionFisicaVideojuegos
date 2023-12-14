#pragma once

#include "RigidBodyForceRegistry.h"
#include "WhirlwindForceGenerator.h"

class RigidBodyManager
{
private:
	list<rigid_body> rigid_bodies_;
	WhirlwindForceGenerator* whirlForceGen_;

	PxPhysics* gPhysics_;
	PxScene* gScene_;
	RigidBodyForceRegistry* rbForceRegistry_;

public:
	RigidBodyManager(PxPhysics* gPhysics, PxScene* gScene);
	virtual ~RigidBodyManager();

	void createGenerators(); // Creacíon de generadores
	void addRigidStatic(Vector3 dim, Vector4 color, Vector3 pos);
	void addRigidDynamic(Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime);
	void update(double t);

	void torbellino();
};

