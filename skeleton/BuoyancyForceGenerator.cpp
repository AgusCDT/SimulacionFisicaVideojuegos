#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d, Particle* p)
{
	height_ = h;
	volume_ = V;
	liquid_density_ = d;
	liquid_particle_ = p;
}

void BuoyancyForceGenerator::updateForce(Particle* p, double t)
{
	float h = p->getPos().y;
	float h0 = liquid_particle_->getPos().y;

	Vector3 f(0, 0, 0);
	float immersed = 0.0f;
	if (h - h0 > height_ * 0.5) {
		immersed = 0.0f;
	}
	else if (h0 - h > height_ * 0.5) {
		// Totally immersed
		immersed = 1.0f;
	}
	else {
		immersed = (h0 - h) / height_ + 0.5;
	}
	f.y = liquid_density_ * volume_ * immersed;

	p->addForce(f);
}
