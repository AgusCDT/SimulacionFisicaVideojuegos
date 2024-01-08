#pragma once
#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "RigidBodyForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "AnchoredSpringFG.h"
#include <vector>

extern bool gameOver_;
const int MAX_RBS = 100; // Número máximo de RBs que pueden existir
const int PLATILLOS_TO_WIN = 1; // Platillos necesarios para ganar

class RigidBodyManager
{
protected:
	list<ParticleGenerator*> particleGenerator_;
	ParticleGenerator* firework_generator_; // This generator is only to shoot the firework!!

	GravityForceGenerator* gForceGen_;
	WhirlwindForceGenerator* whirlForceGen_;
	ExplosionForceGenerator* eForceGen_;
	WindForceGenerator* wForceGen_;

	PxPhysics* gPhysics_;
	PxScene* gScene_;
	RigidBodyForceRegistry* rbForceRegistry_;

	// Atrezzo y obstáculos
	PxRigidStatic* campo_;
	PxRigidStatic* bunkers_[3];
	rigid_body springs_[2];
	AnchoredSpringFG* as1;
	AnchoredSpringFG* as2;

	// Objetos dinámicos: platillos y proyectiles
	list<rigid_body> rigid_bodies_;
	list<rigid_body> shots_;

	// Tiempos de generación de objetos en cada búnker
	double timeBunker1_;
	double timeBunker2_;
	double timeBunker3_;

	bool destroy = false; // Booleano para la detección de destrucción de platillos

	int platillosDestruidos_; // Platillos que vas destruyendo
	double matchTimer_; // Tiempo en partida

	double timeToShoot_ = 0;

public:
	RigidBodyManager(PxPhysics* gPhysics, PxScene* gScene);
	virtual ~RigidBodyManager();

	void createGenerators(); // Creacíon de generadores
	PxRigidStatic* addRigidStatic(int shape, Vector3 dim, Vector4 color, Vector3 pos);
	rigid_body addRigidDynamic(int shape, Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime, int type);
	rigid_body addRigidDynamicShot(int shape, Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime);
	void update(double t);
	void updateDynamic(double t);
	void updateDynamicShot(double t);
	void deleteRBs();
	void generateSemiCircleOrigin();
	void torbellino(); // Añade el generador de torbellino a los RBs
	void explosion(); // Añade el generador de explosión a los RBs
	void viento(); // Añade el generador de viento a los RBs

	void createScenario(); // Creación del atrezzo y los obstáculos
	void generatePlatos(double t); // Generación de los platillos 
	string setScoringText(); // Actualiza el scoring de la partida
	string setWinText(); // Setea el texto de final de partida
	void modifyInertiaTensor(rigid_body rb, double dimx, double dimy, double dimz, int shape); // Modifica el tensor de inercia
	inline int getPlatillosDestruidos() { return platillosDestruidos_; }
	int numRBs_; // Número de RigidBodies
};

