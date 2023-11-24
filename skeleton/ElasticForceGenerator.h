#pragma once
#include "SpringForceGenerator.h"
class ElasticForceGenerator : public SpringForceGenerator
{
public:
	ElasticForceGenerator(double k, double resting_length, Particle* other);
	virtual ~ElasticForceGenerator(){}

	virtual void updateForce(Particle* p, double t) override;
};

