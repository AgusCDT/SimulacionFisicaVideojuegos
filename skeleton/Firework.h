#ifndef FIREWORK_H_
#define FIREWORK_H_
#include "Particle.h"
#include <list>
#include "RigidBodyManager.h"

class ParticleGenerator;
class Firework : public Particle
{
private:
	list<ParticleGenerator*> gens_;
	PxPhysics* gPhysics_;
	PxScene* gScene_;

	Vector3 posRB_;
	Vector3 velRB_;
	int typeRB_;

public:
	Firework(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime) :
		Particle(type, shape, mass, color, pos, vel, accel, damping, lifeTime) {};
	Firework(PxPhysics* gPhysics, PxScene* gScene); // Constructora RBs
	virtual ~Firework() {}

	// The firework generates more fireworks when exploding --> they should be gathered by the System
	list<Particle*> explode();
	list<rigid_body> explodeRB(rigid_body rb);
	void addGenerator(ParticleGenerator* p);
	/*virtual Particle* clone() const;*/
	rigid_body createFireworkRB(Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime);

};
#endif // !FIREWORK_H_

