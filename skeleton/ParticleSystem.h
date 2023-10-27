#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"

class ParticleSystem
{
protected:
	list<Particle*> particles_;
	list<ParticleGenerator*> particleGenerator_;
	ParticleGenerator* firework_generator_; // This generator is only to shoot the firework!!
	Vector3 gravity_;
	Firework* p_ = nullptr;
public:
	ParticleSystem(const Vector3& g = { 0.0f, -10.0f, 0.0f });
	virtual ~ParticleSystem() {};

	void update(double t);

	// Method to generate a Firework with the appropiate type
	void generateFirework(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime);

	ParticleGenerator* getParticleGenerator(const string& n) { return nullptr; } // Gets a particle generator with name...

	void onParticleDeath(Particle* p); // Metodo para eliminar partículas

	void createGenerators(); // Creacíon de genaradores

};

#endif // !PARTICLE_SYSTEM_H_