#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "RenderUtils.hpp"
#include <random>
using namespace physx;
using namespace std;

class Particle : public RenderItem {
protected:
	int type_;
	PxTransform tr_; // A render item le pasaremos la direccion de este transform, para que se actualice automaticamente
	Vector3 vel_;
	Vector3 accel_;
	Vector4 color_;
	RenderItem* renderItem_ = nullptr;

	float inverse_mass_;
	float damping_;

	double lifeTime_;

public:
	Particle() {}
	Particle(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime);
	virtual ~Particle();

	bool integrate(double t);

	inline int getType() { return type_; }
	inline Vector3 getVel() { return vel_; }
	inline void setPos(Vector3 pos) { tr_.p = pos; }
	/*virtual Particle* clone() const;*/
	double timer_ = 0;


	// Accumulated force
	Vector3 force_accum_;

	// Clears accumulated force
	inline void clearForce() { force_accum_ *= 0.0; }

	// Add force to apply in next integration only
	inline void addForce(const Vector3& f) { force_accum_ += f; }

	inline float getInverseMass() { return inverse_mass_; }
};

#endif // !PARTICLE_H_