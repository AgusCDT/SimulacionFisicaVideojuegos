#ifndef PARTICLE_DRAG_GENERATOR_H_
#define PARTICLE_DRAG_GENERATOR_H_

#include "ForceGenerator.h"
#include "core.hpp"

class ParticleDragGenerator : public ForceGenerator
{
protected:
	float k1_; // Coef for velocity
	float k2_; // Coef for square velocity
public:
	ParticleDragGenerator() {}
	ParticleDragGenerator(const float k1, const float k2);
	virtual void updateForce(Particle* p, double t);
	inline void setDrag(float k1, float k2) { k1_ = k1; k2_ = k2; }
	inline float getK1() { return k1_; }
	inline float getK2() { return k2_; }
};
#endif // ! PARTICLE_DRAG_GENERATOR_H_
