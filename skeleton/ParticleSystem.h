#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"

#include "ParticleDragGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "ElasticForceGenerator.h"
#include "BuoyancyForceGenerator.h"

class ParticleSystem
{
protected:
	list<Particle*> particles_;
	list<ParticleGenerator*> particleGenerator_;
	ParticleGenerator* firework_generator_; // This generator is only to shoot the firework!!
	Vector3 gravity_;
	Firework* p_ = nullptr;
	Particle* part_ = nullptr; 

	ParticleForceRegistry* pForceRegistry_;
	list<ForceGenerator*> forceGenerators_;
	GravityForceGenerator* gForceGen1_;
	GravityForceGenerator* gForceGen2_;
	WindForceGenerator* wForceGen_;
	WhirlwindForceGenerator* whirlForceGen_;
	ExplosionForceGenerator* eForceGen_;

	AnchoredSpringFG* f3;
	BuoyancyForceGenerator* b1;

	bool generaFirework_ = true;
public:
	ParticleSystem();
	virtual ~ParticleSystem();

	void update(double t);

	// Method to generate a Firework with the appropiate type
	void generateFirework(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime);
	void generateTracaFinal(); // Genera los fireworks cuando la partida acaba
	void generateForcedParticle(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime);

	ParticleGenerator* getParticleGenerator(const string& n) { return nullptr; } // Gets a particle generator with name...

	void onParticleDeath(Particle* p); // Metodo para eliminar part�culas

	void createGenerators(); // Creac�on de generadores

	void gravedad(Vector3 g);
	void viento();
	void torbellino();
	void explosion(); // A�ade el generador de explosion a las part�culas

	void generateSpringDemo1();
	void generateSpringDemo2();
	inline void moreSpringK(double k){ f3->moreK(k); }
	inline void lessSpringK(double k) { f3->lessK(k); }
	void generateElasticBand();
	void generateSlinky();
	void generateBuoyancyDemo();
	inline void changeVolume() { b1->changeVolume(); }
	inline void changeLiquidDensity(float d) { b1->changeLiquidDensity(d); }
};

#endif // !PARTICLE_SYSTEM_H_