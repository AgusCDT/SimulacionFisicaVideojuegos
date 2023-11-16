#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(float K, float timeConst, Vector3 origin, float vel, float radius)
{
	K_ = K;
	timeConst_ = timeConst;
	vel_ = vel;
	origin_ = origin;
	radius_ = radius;
}

void ExplosionForceGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInverseMass()) < 1e-10) {
		return;
	}

	radius_ += vel_ * t; // Aumento del radio de la explosion conforme al tiempo

	Vector3 distance = p->getPos() - origin_; 
	float r = sqrt(pow(distance.x, 2) + pow(distance.y, 2) + pow(distance.z, 2)); // Distancia a la explosion

	if (r < radius_)
	{
		Vector3 f = (K_ / (r * r)) * distance * exp(-t / timeConst_);
		p->addForce(f);
	}
}
