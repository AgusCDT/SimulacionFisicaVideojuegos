#ifndef FIREWORK_H_
#define FIREWORK_H_
#include "Particle.h"
#include <list>
class ParticleGenerator;
class Firework : public Particle
{
private:
	list<ParticleGenerator*> gens_;

public:
	Firework(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime) :
		Particle(type, shape, mass, color, pos, vel, accel, damping, lifeTime) {};
	virtual ~Firework() {}

	// The firework generates more fireworks when exploding --> they should be gathered by the System
	list<Particle*> explode();
	void addGenerator(ParticleGenerator* p);
	/*virtual Particle* clone() const;*/

};
#endif // !FIREWORK_H_

