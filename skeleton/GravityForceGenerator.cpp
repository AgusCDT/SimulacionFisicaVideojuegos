#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g)
{
	gravity_ = g;
}

void GravityForceGenerator::updateForce(Particle* p, double t)
{
	// Check that the particle has Finite MAss
	if (fabs(p->getInverseMass()) < 1e-10) {
		return;
	}
	// Apply the mass scaled gravity
	p->addForce(gravity_ * (1 / p->getInverseMass()));
}

void GravityForceGenerator::updateForce(rigid_body rb, double t)
{
	rb.body_->addForce(gravity_ * rb.body_->getMass());
}
