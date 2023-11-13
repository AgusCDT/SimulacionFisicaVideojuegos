#include "ParticleForceRegistry.h"

void ParticleForceRegistry::updateForces(double duration)
{
	for (auto it = begin(); it != end(); it++) {
		it->first->updateForce(it->second, duration);
	}
}

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p)
{
	insert(FRPair(fg, p));
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p)
{
	auto it = begin();
	while (it != end()) {
		if (it->second != p) {
			it++;
		}
		else {
			it = this->erase(it);
		}
	}
}

void ParticleForceRegistry::deleteForceRegistry(ForceGenerator* fg)
{
	auto it = begin();
	while (it != end()) {
		if (it->first != fg) {
			it++;
		}
		else {
			it = this->erase(it);
		}
	}
}
