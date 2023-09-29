#pragma once

#include "RenderUtils.hpp"
using namespace physx;

class Particle : public RenderItem {
public: 
	Particle(physx::PxShape* _shape, float mass, Vector4 color, Vector3 accel, float damping);
	~Particle();

	void integrate(double t);

	inline void setAcceleration(float x, float y, float z) { accel_ = { x, y, z }; }
	
	inline float getAccelX(){
		return accel_.x;
	}

private:
	Vector3 vel_;
	Vector3 accel_;
	Vector4 color_;
	physx::PxTransform tr_; // A render item le pasaremos la direccion de este transform, para que se actualice automaticamnete
	RenderItem* renderItem_;

	float inverse_mass_;
	float damping_;
};
