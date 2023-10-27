#ifndef UNIFORM_PARTICLE_GENERATOR_H_
#define UNIFORM_PARTICLE_GENERATOR_H_
#include "ParticleGenerator.h"
class UniformParticleGenerator : public ParticleGenerator
{
private:
	Vector3 vel_width_, pos_width_;
	uniform_real_distribution<double> d_{ 0, 1 };
	uniform_real_distribution<double> dAux_{ 1, 5 };
public:
	UniformParticleGenerator(Vector3 vel_width, Vector3 pos_width);
	virtual ~UniformParticleGenerator() {}

	virtual list<Particle*> generateParticles(int type) override;
	list<Particle*> generateRain();
};
#endif // !UNIFORM_PARTICLE_GENERATOR_H_

