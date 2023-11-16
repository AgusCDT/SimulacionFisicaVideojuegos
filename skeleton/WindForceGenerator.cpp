#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(const float k1, const float k2, Vector3 windVel, Vector3 origin, Vector3 size) : ParticleDragGenerator(k1, k2)
{
	windVel_ = windVel;
	origin_ = origin;
	size_ = size;
}

void WindForceGenerator::updateForce(Particle* p, double t)
{
	if (withinBox(p)) {
		if (fabs(p->getInverseMass()) < 1e-10) return;

		Vector3 v = p->getVel();
		Vector3 diffVel = windVel_ - v; // Diferencia de velocidad
		Vector3 dragF;
		dragF = k1_ * diffVel + k2_ * diffVel.magnitude() * diffVel;

		p->addForce(dragF);
	}
}

bool WindForceGenerator::withinBox(Particle* p)
{
	Vector3 pos = p->getPos();
	if ((pos.x >= origin_.x && pos.x <= origin_.x + size_.x) &&
		(pos.y >= origin_.y && pos.y <= origin_.y + size_.y) &&
		(pos.z >= origin_.z && pos.z <= origin_.z + size_.z)) {

		return true;
	}
	else {
		cout << "Out" << endl;
		return false;
	}
}
