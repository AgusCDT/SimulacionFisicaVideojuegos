#ifndef WHIRLWIND_FORCE_GENERATOR_H_
#define WHIRLWIND_FORCE_GENERATOR_H_

#include "WindForceGenerator.h"
class WhirlwindForceGenerator : public WindForceGenerator
{
public:
	WhirlwindForceGenerator(const float K, Vector3 origin, Vector3 size);
	virtual ~WhirlwindForceGenerator() {}

	virtual void updateForce(Particle* p, double t) override;
	virtual void updateForce(rigid_body rb, double t) override;

	virtual bool withinBox(Particle* p) override;
};
#endif // !WHIRLWIND_FORCE_GENERATOR_H_

