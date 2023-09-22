#pragma once

#include "RenderUtils.hpp"
using namespace physx;

class Particle {
public: Particle(Vector3 pos, Vector3 vel);
	    ~Particle();

	  void integrate(double t);

private:
	Vector3 vel_;
	physx::PxTransform pos_;
	RenderItem* renderItem;
};
