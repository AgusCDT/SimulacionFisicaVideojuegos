#ifndef EXPLOSION_FORCE_GENERATOR_H_
#define EXPLOSION_FORCE_GENERATOR_H_

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
	virtual ~ExplosionForceGenerator() {}
	virtual void updateForce(Particle* particle, double t);
	virtual void updateForce(rigid_body rb, double t);
};
#endif // !EXPLOSION_FORCE_GENERATOR_H_

