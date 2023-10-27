#include "Firework.h"
#include "ParticleGenerator.h"

list<Particle*> Firework::explode()
{
	gens_.front()->setOrigin(tr_.p);
	gens_.front()->setMeanVelocity(vel_);
	return gens_.front()->generateParticles(type_);
}

void Firework::addGenerator(ParticleGenerator* p)
{
	gens_.push_back(p);
}