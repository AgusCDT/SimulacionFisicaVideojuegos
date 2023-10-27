#ifndef GAUSSIAN_PARTICLE_GENERATOR_H_
#define GAUSSIAN_PARTICLE_GENERATOR_H_
#include "ParticleGenerator.h"
#include <iostream>
#include <random>
#include <time.h>

class GaussianParticleGenerator : public ParticleGenerator
{
protected:
	Vector3 std_dev_pos_, std_dev_vel_;
	double m_ = 1, v_ = 4;
	normal_distribution<double> d_{ m_, v_ }; // Use it as a base for generating normal numbers!
	normal_distribution<double> dAux1_{ 0.4, 1.0 };
	normal_distribution<double> dAux2_{ 0, 2 };

public:
	GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel);
	virtual ~GaussianParticleGenerator() {}

	virtual list<Particle*> generateParticles(int type) override;

	list<Particle*> generateFirework1();
	list<Particle*> generateFirework2();
	list<Particle*> generateFireworkCircle();
	list<Particle*> generateFireworkSnowy();

	inline void changeDistribution(double m, double v) { m_ = m; v_ = v; };
};
#endif // !GAUSSIAN_PARTICLE_GENERATOR_H_