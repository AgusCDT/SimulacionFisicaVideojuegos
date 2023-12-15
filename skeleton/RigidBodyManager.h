#pragma once

#include "RigidBodyForceRegistry.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "AnchoredSpringFG.h"

const int MAX_RBS = 1000; // Número máximo de RBs que pueden existir

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

	int numRBs_; // Número de RigidBodies

public:
	RigidBodyManager(PxPhysics* gPhysics, PxScene* gScene);
	virtual ~RigidBodyManager();

	void createGenerators(); // Creacíon de generadores
	void addRigidStatic(Vector3 dim, Vector4 color, Vector3 pos);
	void addRigidDynamic(Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime);
	void update(double t);

	void torbellino(); // Añade el generador de torbellino a los RBs
	void explosion(); // Añade el generador de explosión a los RBs
	void viento(); // Añade el generador de viento a los RBs
	void generateSpringDemo1(); // Demo de un RB conectado a una partícula
};

