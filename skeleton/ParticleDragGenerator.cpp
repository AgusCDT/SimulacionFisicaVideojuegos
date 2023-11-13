#include "ParticleDragGenerator.h"

ParticleDragGenerator::ParticleDragGenerator(const float k1, const float k2)
{
	k1_ = k1;
	k2_ = k2;
}

void ParticleDragGenerator::updateForce(Particle* p, double t)
{
	//Check that the particle has Finite Mass
	if (fabs(p->getInverseMass() < 1e-10)) {
		return;
	}
	// Compute the drag force 
	Vector3 v = p->getVel();
	float drag_coef_ = v.normalize();
	Vector3 dragF;
	drag_coef_ = k1_ * drag_coef_ + k2_ * drag_coef_ * drag_coef_;
	dragF = -v * drag_coef_;
	// Apply the drag force
	cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << endl;
	p->addForce(dragF);
}
