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
public:
	ParticleSystem();
	virtual ~ParticleSystem() {};

	void update(double t);

	// Method to generate a Firework with the appropiate type
	void generateFirework(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime);

	void generateForcedParticle(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime);

	ParticleGenerator* getParticleGenerator(const string& n) { return nullptr; } // Gets a particle generator with name...

	void onParticleDeath(Particle* p); // Metodo para eliminar partículas

	void createGenerators(); // Creacíon de generadores

	void explosion(); // Añade el generador de explosion a las partículas

};

#endif // !PARTICLE_SYSTEM_H_