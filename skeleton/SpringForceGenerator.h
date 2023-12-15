#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator
{
protected:
	double k_;
	double resting_length_;
	Particle* other_;
	rigid_body otherRB_;
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	SpringForceGenerator(double k, double resting_length, rigid_body other);
	virtual ~SpringForceGenerator(){}

	virtual void updateForce(Particle* p, double t);
	virtual void updateForce(rigid_body rb, double t);

	inline void moreK(double k) { k_ += k; }
	inline void lessK(double k) { k_ -= k; }
};

