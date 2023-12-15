#pragma once

#include "RigidBodyForceRegistry.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "AnchoredSpringFG.h"

const int MAX_RBS = 1000; // N�mero m�ximo de RBs que pueden existir

class RigidBodyManager
{
private:
	list<rigid_body> rigid_bodies_;
	WhirlwindForceGenerator* whirlForceGen_;
	ExplosionForceGenerator* eForceGen_;
	WindForceGenerator* wForceGen_;

	AnchoredSpringFG* f3;

	PxPhysics* gPhysics_;
	PxScene* gScene_;
	RigidBodyForceRegistry* rbForceRegistry_;

	int numRBs_; // N�mero de RigidBodies

public:
	RigidBodyManager(PxPhysics* gPhysics, PxScene* gScene);
	virtual ~RigidBodyManager();

	void createGenerators(); // Creac�on de generadores
	void addRigidStatic(Vector3 dim, Vector4 color, Vector3 pos);
	void addRigidDynamic(Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime);
	void update(double t);

	void torbellino(); // A�ade el generador de torbellino a los RBs
	void explosion(); // A�ade el generador de explosi�n a los RBs
	void viento(); // A�ade el generador de viento a los RBs
	void generateSpringDemo1(); // Demo de un RB conectado a una part�cula
};

