#include "ParticleDragGenerator.h"

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
