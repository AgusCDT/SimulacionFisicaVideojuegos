#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other)
{
	k_ = k;
	resting_length_ = resting_length;
	other_ = other;
}

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, rigid_body other)
{
	k_ = k;
	resting_length_ = resting_length;
	otherRB_ = other;
}

void SpringForceGenerator::updateForce(Particle* p, double t)
{
	// Particle is the particle to apply the force 
	Vector3 relative_pos_vector = other_->getPos() - p->getPos();
	Vector3 force;

	// normalize: Normalize the relative_pos_vector and return its length
	const float length = relative_pos_vector.normalize();
	const float delta_x = length - resting_length_;

	force = relative_pos_vector * delta_x * k_;
	p->addForce(force);
}

void SpringForceGenerator::updateForce(rigid_body rb, double t)
{
	// Particle is the particle to apply the force 
	Vector3 relative_pos_vector = other_->getPos() - rb.body_->getGlobalPose().p;
	Vector3 force;

	// normalize: Normalize the relative_pos_vector and return its length
	const float length = relative_pos_vector.normalize();
	const float delta_x = length - resting_length_;

	force = relative_pos_vector * delta_x * k_;
	rb.body_->addForce(force);
}
