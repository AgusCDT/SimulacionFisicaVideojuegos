#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"

class ParticleSystem
{
private:
	list<Particle*> particles_;
	list<ParticleGenerator*> particleGenerator_;

public:
	void update(double t);
	/*ParticleGenerator* getParticleGenerator(string name) {
		return particleGenerator_;
	}*/

	void generateFireworkSystem() {}

	// Metodo para eliminar partículas: si su tiempo de vida se acaba o se va fuera de la pantalla

};

#endif // !PARTICLE_SYSTEM_H_



