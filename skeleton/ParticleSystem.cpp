#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const Vector3& g)
{
	gravity_ = g;
	firework_generator_ = new UniformParticleGenerator(Vector3{ 40,40,40 }, Vector3{ 20,20,20 });
	particleGenerator_.push_back(firework_generator_);
	/*firework_generator_ = new GaussianParticleGenerator(Vector3{ 40,40,40 }, Vector3{ 20,20,20 });
	particleGenerator_.push_back(firework_generator_);*/
}

void ParticleSystem::update(double t)
{
	auto a = particles_.begin();

	list<Particle*>::iterator it = particles_.begin();
	while (it != particles_.end()) {
		auto aux = it;
		++aux;
		if ((*it)->integrate(t)) {
			std::list<Particle*> p = particleGenerator_.front()->generateParticles(F);
			for (auto d : p) {
				particles_.push_back(d);
			}
			onParticleDeath(*it);
		}
		it = aux;
	}
}

void ParticleSystem::generateFirework(ParticleType firework_type) 
{
	p_ = new Particle(firework_type, CreateShape(PxSphereGeometry(0.1)),
					2.0f, // Mass
					Vector4(1.0f, 0.4f, 0.2f, 1.0f), // Color
					GetCamera()->getTransform().p,
					Vector3(GetCamera()->getDir() * 35.0f), // Vel  
					Vector3(0.0f, -1.0f, 0.0f), // Accel
					0.9f, 
					3.0f);
	particles_.push_back(p_);

	particleGenerator_.push_back(firework_generator_);
}

void ParticleSystem::onParticleDeath(Particle* p)
{
	particles_.remove(p);
	delete p;
}
