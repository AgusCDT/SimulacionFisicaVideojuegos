#ifndef GRAVITY_FORCE_GENERATOR_H_
#define GRAVITY_FORCE_GENERATOR_H_

#include "ForceGenerator.h"
#include "core.hpp"

class GravityForceGenerator : public ForceGenerator
{
protected:
	Vector3 gravity_;
public:
	GravityForceGenerator(const Vector3& g);

	virtual void updateForce(Particle* p, double t);

	inline void setGravity(Vector3 g) { gravity_ = g; }
};
#endif // !GRAVITY_FORCE_GENERATOR_H_



