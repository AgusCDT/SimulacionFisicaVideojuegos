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
const int MAX_RBS = 1000; // N�mero m�ximo de RBs que pueden existir
const int PLATILLOS_TO_WIN = 10; // Platillos necesarios para ganar

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

	// Atrezzo y obst�culos
	PxRigidStatic* campo_;
	PxRigidStatic* bunkers_[3];
	rigid_body springs_[2];
	AnchoredSpringFG* as1;
	AnchoredSpringFG* as2;

	// Objetos din�micos: platillos y proyectiles
	list<rigid_body> rigid_bodies_;
	list<rigid_body> shots_;

	// Tiempos de generaci�n de objetos en cada b�nker
	double timeBunker1_;
	double timeBunker2_;
	double timeBunker3_;

	bool destroy = false; // Booleano para la detecci�n de destrucci�n de platillos

	int platillosDestruidos_; // Platillos que vas destruyendo
	double matchTimer_; // Tiempo en partida

	double timeToShoot_ = 0; // Tiempo para manejar cuando disparar

public:
	RigidBodyManager(PxPhysics* gPhysics, PxScene* gScene);
	virtual ~RigidBodyManager();

	void createGenerators(); // Creac�on de generadores
	PxRigidStatic* addRigidStatic(int shape, Vector3 dim, Vector4 color, Vector3 pos);
	rigid_body addRigidDynamic(int shape, Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime, int type);
	rigid_body addRigidDynamicShot(int shape, Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime);
	void update(double t);
	void updateDynamic(double t); // Actualiza los platillos
	void updateDynamicShot(double t); // Actualiza los disparos
	void deleteRBs(); // Elimina los RBs
	void generateSemiCircleOrigin(); // Genera el RB origen para la generaci�n de platillos en semicirculo
	void torbellino(); // A�ade el generador de torbellino a los RBs
	void explosion(); // A�ade el generador de explosi�n a los RBs
	void viento(); // A�ade el generador de viento a los RBs

	void createScenario(); // Creaci�n del atrezzo y los obst�culos
	void generatePlatos(double t); // Generaci�n de los platillos 
	string setScoringText(); // Actualiza el scoring de la partida
	string setWinText(); // Setea el texto de final de partida
	void modifyInertiaTensor(rigid_body rb, double dimx, double dimy, double dimz, int shape); // Modifica el tensor de inercia
	inline int getPlatillosDestruidos() { return platillosDestruidos_; }
	int numRBs_; // N�mero de RigidBodies
};

