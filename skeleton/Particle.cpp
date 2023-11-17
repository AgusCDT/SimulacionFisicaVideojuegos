#include "Particle.h"

Particle::Particle(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime) {
	type_ = type;
	vel_ = vel;
	accel_ = accel;
	inverse_mass_ = 1 / mass;
	damping_ = damping;
	tr_.p = pos;
	tr_.q = { 0, 0, 0, 0 };
	lifeTime_ = lifeTime;

	force_accum_ = { 0, 0, 0 };
	renderItem_ = new RenderItem(shape, &tr_, color);
}

Particle::~Particle() { DeregisterRenderItem(renderItem_); }

bool Particle::integrate(double t) {
	timer_ += t;

	Vector3 resulting_accel_;
	// Get the accel considering the force accum
	resulting_accel_ = accel_ + force_accum_ * inverse_mass_;
	
	vel_ += resulting_accel_ * t;
	
	// Update linear velocity
	//vel_ += accel_ * t;
	// Impose drag (damping)
	vel_ *= powf(damping_, t);
	// Update position
	tr_.p += vel_ * t;

	// Clear accum
	clearForce();

	if (timer_ >= lifeTime_) {
		return true;
	}
	else {
		return false;
	}
}