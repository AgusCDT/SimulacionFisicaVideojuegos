#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator : public ParticleGenerator
{
protected:
	Vector3 vel_width_, pos_width_;
	uniform_real_distribution<double> d_{ 0, 1 };
	uniform_real_distribution<double> dAux_{ 1, 2 };
public:
	UniformParticleGenerator(Vector3 vel_width, Vector3 pos_width);
	~UniformParticleGenerator() {}

	virtual list<Particle*> generateParticles(ParticleType type) override;
};

