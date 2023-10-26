#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include <list>
#include "Particle.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"

class ParticleSystem
{
protected:
	list<Particle*> particles_;
	list<ParticleGenerator*> particleGenerator_;
	ParticleGenerator* firework_generator_; // This generator is only to shoot the firework!!
	Vector3 gravity_;
	/*vector<Firework*> _firework_pool;*/ // Fireworks to be used as models!

	Particle* p_ = nullptr;
public:
	ParticleSystem(const Vector3& g = { 0.0f, -9.8f, 0.0f});
	virtual ~ParticleSystem() {};

	void update(double t);

	// Method to generate a Firework with the appropiate type
	void generateFirework(ParticleType firework_type);

	ParticleGenerator* getParticleGenerator(const string& n) { return nullptr; } // Gets a particle generator with name...

	void onParticleDeath(Particle* p); // Metodo para eliminar partículas

};

#endif // !PARTICLE_SYSTEM_H_



