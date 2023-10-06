#ifndef PARTICLE_GENERATOR_H_
#define PARTICLE_GENERATOR_H_

#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>

using namespace physx;
using namespace std;

class ParticleGenerator
{
private:
	string name_;
	Vector3 meanPos_;
	Vector3 meanVel_;
	double genProbability_;
	int numParticles_;

public:
	void setParticle(Particle* model);
	virtual list<Particle*> generateParticles();

};

#endif // !PARTICLE_GENERATOR_



