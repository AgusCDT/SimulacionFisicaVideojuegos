#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "RenderUtils.hpp"
using namespace physx;

enum ParticleType { F, G }; // Enum
class Particle : public RenderItem {	   
private:
	PxTransform tr_; // A render item le pasaremos la direccion de este transform, para que se actualice automaticamente
	Vector3 vel_;
	Vector3 accel_;
	Vector4 color_;
	RenderItem* renderItem_ = nullptr;

	float inverse_mass_;
	float damping_;

	double timer_ = 0;
	double lifeTime_;
	ParticleType type_;

public:
	Particle(ParticleType type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double leftTime);
	~Particle();

	bool integrate(double t);

	inline ParticleType getType() { return type_; }
	inline Vector3 getVel() { return vel_; }
	inline double getTimer() { return timer_; }

	inline void setTimer(double t) { timer_ = t; }
	inline void setPos(Vector3 pos) { tr_.p = pos; }
	/*virtual Particle* clone() const;*/
};

#endif // !PARTICLE_H_