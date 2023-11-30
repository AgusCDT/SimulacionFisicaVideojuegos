#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator
{
protected:
	double k_;
	double resting_length_;
	Particle* other_;
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	virtual ~SpringForceGenerator(){}

	virtual void updateForce(Particle* p, double t);

	inline void moreK(double k) { k_ += k; }
	inline void lessK(double k) { k_ -= k; }
};

