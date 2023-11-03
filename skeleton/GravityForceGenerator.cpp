#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* p, double t)
{
	// Check that the particle has Finite MAss
	if (fabs(p->getInverseMass()) < 1e-10) {
		return;
	}
	// Apply the mass scaled gravity
	p->addForce(gravity_ * (1 / p->getInverseMass()));
}
