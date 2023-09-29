#include "Particle.h"

Particle::Particle(physx::PxShape* shape, float mass, Vector4 color, Vector3 accel, float damping) {
	vel_ = { 0.0f, 0.0f, 0.0f };
	accel_ = accel;
	inverse_mass_ = 1 / mass;
	damping_ = damping;
	tr_.p = { 0, 0, 0 };
	tr_.q = { 0, 0, 0, 0 };

	renderItem_ = new RenderItem(shape, &tr_, color);
}

Particle::~Particle() {}

void Particle::integrate(double t) {
	// Trivial case, infinite mass --> do nothing
	if (inverse_mass_ <= 0.0f) return;
	// Update position
	tr_.p += vel_ * t;
	// Update linear velocity
	vel_ += accel_ * t;
	// Impose drag (damping)
	vel_ *= powf(damping_, t);
}