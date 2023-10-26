#include "Particle.h"

Particle::Particle(ParticleType type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime) {
	type_ = type;
	vel_ = vel;
	accel_ = accel;
	inverse_mass_ = 1 / mass;
	damping_ = damping;
	tr_.p = pos;
	tr_.q = { 0, 0, 0, 0 };
	lifeTime_ = lifeTime;

	renderItem_ = new RenderItem(shape, &tr_, color);
}

Particle::~Particle() {}

bool Particle::integrate(double t) {
	timer_ += t;

	// Trivial case, infinite mass --> do nothing
	/*if (inverse_mass_ <= 0.0f) return;*/
	// Update position
	tr_.p += vel_ * t;
	// Update linear velocity
	vel_ += accel_ * t;
	// Impose drag (damping)
	vel_ *= powf(damping_, t);

	if (timer_ >= lifeTime_) {
		return true;
	}
	else {
		return false;
	}
}