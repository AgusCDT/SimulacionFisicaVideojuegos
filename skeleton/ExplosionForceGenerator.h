#pragma once
#include "ForceGenerator.h"
class ExplosionForceGenerator : public ForceGenerator
{
protected:
	Vector3 origin_;
	float K_;
	float timeConst_;
	float vel_;
	float radius_;

public:
	ExplosionForceGenerator(float K, float timeConst, Vector3 origin, float vel, float radius);

	virtual void updateForce(Particle* particle, double t);

};

