#ifndef PARTICLE_FORCE_REGISTRY_H_
#define PARTICLE_FORCE_REGISTRY_H_

#include <map>
#include "ForceGenerator.h"
#include <list>

typedef pair<ForceGenerator*, Particle*> FRPair;
class ParticleForceRegistry : public multimap<ForceGenerator*, Particle*>
{
public:
	void updateForces(double duration);

	void addRegistry(ForceGenerator* fg, Particle* p);

	void deleteParticleRegistry(Particle* p);

	void deleteForceRegistry(ForceGenerator* fg);
};

#endif // !PARTICLE_FORCE_REGISTRY_H_