#pragma once

#include "RigidBodyForceRegistry.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "AnchoredSpringFG.h"
#include <vector>

const int MAX_RBS = 10; // Número máximo de RBs que pueden existir

class RigidBodyManager
{
private:
	
	WhirlwindForceGenerator* whirlForceGen_;
	ExplosionForceGenerator* eForceGen_;
	WindForceGenerator* wForceGen_;

	AnchoredSpringFG* f3;

	PxPhysics* gPhysics_;
	PxScene* gScene_;
	RigidBodyForceRegistry* rbForceRegistry_;

	

	PxRigidStatic* campo_;
	PxRigidStatic* bunkers_[3];

	
	list<rigid_body> rigid_bodies_;
	list<rigid_body> shots_;
	// Tiempos de generación de objetos en cada búnker
	double timeBunker1_;
	double timeBunker2_;
	double timeBunker3_;

	bool destroy = false;

	int platillosDestruidos_;

public:
	RigidBodyManager(PxPhysics* gPhysics, PxScene* gScene);
	virtual ~RigidBodyManager();

	void createGenerators(); // Creacíon de generadores
	PxRigidStatic* addRigidStatic(int shape, Vector3 dim, Vector4 color, Vector3 pos);
	rigid_body addRigidDynamic(int shape, Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime);
	rigid_body addRigidDynamicShot(int shape, Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime);
	void update(double t);

	void torbellino(); // Añade el generador de torbellino a los RBs
	void explosion(); // Añade el generador de explosión a los RBs
	void viento(); // Añade el generador de viento a los RBs
	void generateSpringDemo1(); // Demo de un RB conectado a una partícula


	void createScenario();

	void collisions();

	void generatePlatos(double t);

	void scoring();

	inline int getPlatillosDestruidos() { return platillosDestruidos_; }

	int numRBs_; // Número de RigidBodies

	
};

