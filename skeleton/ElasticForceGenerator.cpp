#include "ElasticForceGenerator.h"

ElasticForceGenerator::ElasticForceGenerator(double k, double resting_length, Particle* other) : SpringForceGenerator(k, resting_length, other)
{
}

void ElasticForceGenerator::updateForce(Particle* p, double t)
{
	// Particle is the particle to apply the force 
	Vector3 relative_pos_vector = other_->getPos() - p->getPos();
	if (relative_pos_vector.magnitude() > resting_length_) {
		Vector3 force;

		// normalize: Normalize the relative_pos_vector and return its length
		const float length = relative_pos_vector.normalize();
		const float delta_x = length - resting_length_;
		force = relative_pos_vector * delta_x * k_;
		p->addForce(force);
		/*cout << "X: " << p->getPos().x << endl;*/
		/*cout << "Y: " << p->getPos().y << endl;*/
	}
}
