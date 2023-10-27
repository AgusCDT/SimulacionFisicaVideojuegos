#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const Vector3& g)
{
	gravity_ = g;
	createGenerators();
}

void ParticleSystem::update(double t)
{
	list<Particle*>::iterator it = particles_.begin();
	while (it != particles_.end()) {
		auto aux = it;
		++aux;
		if ((*it)->integrate(t)) {
			if ((*it)->getType() >= 1) {
				Firework* firework = static_cast<Firework*>(*it);
				list<Particle*> p = firework->explode();
				for (auto d : p) {
					particles_.push_back(d);
				}
			}
			onParticleDeath(*it);
		}
		it = aux;
	}
}

void ParticleSystem::generateFirework(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime)
{
	p_ = new Firework(type, shape,
		mass, // Mass
		color, // Color
		pos, // Pos
		vel, // Vel  
		accel, // Accel
		damping,
		lifeTime);
	particles_.push_back(p_);
	if (type != 5) {
		p_->addGenerator(particleGenerator_.back()); // Unif.
	}
	else {
		p_->addGenerator(particleGenerator_.front()); // Gauss
	}
}

void ParticleSystem::onParticleDeath(Particle* p)
{
	particles_.remove(p);
	delete p;
}

void ParticleSystem::createGenerators()
{
	firework_generator_ = new UniformParticleGenerator(Vector3{ 40,40,40 }, Vector3{ 50,50,50 });
	particleGenerator_.push_back(firework_generator_);
	firework_generator_ = new GaussianParticleGenerator(Vector3{ 40,40,40 }, Vector3{ 20,20,20 });
	particleGenerator_.push_back(firework_generator_);
}
