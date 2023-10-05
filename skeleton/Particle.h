#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "RenderUtils.hpp"
using namespace physx;

class Particle : public RenderItem {

private:
	PxTransform tr_; // A render item le pasaremos la direccion de este transform, para que se actualice automaticamente
	Vector3 vel_;
	Vector3 accel_;
	Vector4 color_;
	RenderItem* renderItem_ = nullptr;

	float inverse_mass_;
	float damping_;

public:
	Particle(PxShape* shape, float mass, Vector4 color, Vector3 vel, Vector3 accel, float damping);
	~Particle();

	void integrate(double t);
};

#endif // !PARTICLE_H_