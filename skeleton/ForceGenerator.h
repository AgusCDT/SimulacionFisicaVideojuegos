#ifndef FORCE_GENERATOR_H_
#define FORCE_GENERATOR_H_

#include "Particle.h"
#include <iostream>

using namespace std;
class ForceGenerator
{
public:
	virtual void updateForce(Particle* p, double t) = 0;
	virtual void updateForce(rigid_body rb, double t) = 0;
	string name_;
	double t_ = 0.0; // If starting negative --> eternal
	double duration_ = -1e10;

	inline bool updateTime(double t) { 
		t_ += t; 
		return t_ < duration_ || duration_ < 0.0; // Devuelve true si ya era cero o si es positivo
	}

	virtual ~ForceGenerator() {}
};
#endif // !FORCE_GENERATOR_H_



