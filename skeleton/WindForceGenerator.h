#ifndef WIND_FORCE_GENERATOR_H_
#define WIN_FORCE_GENERATOR_H_

#include "ParticleDragGenerator.h"
class WindForceGenerator : public ParticleDragGenerator
{
protected:
	Vector3 windVel_;
	Vector3 origin_;
	Vector3 size_;
public:
	WindForceGenerator(const float k1, const float k2, Vector3 windVel, Vector3 origin, Vector3 size);
	virtual void updateForce(Particle* p, double t) override;

	virtual bool withinBox(Particle* p); // Comprueba si la particula esta dentro del rango de accion del viento
};
#endif // !WIND_FORCE_GENERATOR_H_



