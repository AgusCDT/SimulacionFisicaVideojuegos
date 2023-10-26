#pragma once
#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator
{
protected: 
	Vector3 std_dev_pos_, std_dev_vel_;
	normal_distribution<double> d_{ 0,1 }; // Use it as a base for generating normal numbers!
	normal_distribution<double> dAux1_{ 1,2 }; 
	normal_distribution<double> dAux2{ 0.05, 0.1 };

public:
	GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel);
	~GaussianParticleGenerator() {}

	virtual list<Particle*> generateParticles(ParticleType type) override;
};

