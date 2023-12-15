#pragma once
#include "ForceGenerator.h"
class BuoyancyForceGenerator : public ForceGenerator
{
protected:
	float height_;
	float volume_;
	float liquid_density_;

	Particle* liquid_particle_;
public:
	BuoyancyForceGenerator(float h, float V, float d, Particle* p);
	virtual ~BuoyancyForceGenerator(){}

	virtual void updateForce(Particle* p, double t);
	virtual void updateForce(rigid_body rb, double t);

	inline void changeVolume() { volume_ += 0.5f; }
	inline void changeLiquidDensity(float d) { liquid_density_ = d; }
};

