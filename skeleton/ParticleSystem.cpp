#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(ParticleForceRegistry* pForceRegistry/*const Vector3& g*/)
{
	/*gravity_ = g;*/
	pForceRegistry_ = pForceRegistry;
	createGenerators();
	
}

void ParticleSystem::update(double t)
{
	// RECORRER LISTA DE GENERADORES DE FUERZA
	/*list<ForceGenerator*>::iterator itF = forceGenerators_.begin();
	while (itF != forceGenerators_.end()) {
		auto aux = itF;
		++aux;
		if ((*itF)->updateTime(t)) {
			pForceRegistry_->deleteForceRegistry((*itF));
		}
		itF = aux;
	}*/


	list<Particle*>::iterator it = particles_.begin();
	while (it != particles_.end()) {
		auto aux = it;
		++aux;
		if ((*it)->getType() == 2) {
			(*it)->addForce({0, 20, 0 });
		}
		else if ((*it)->getType() == 5) {
			(*it)->addForce({ 0, 20, 0 });
		}
		cout << to_string((*it)->getVel().y) << endl;
		if ((*it)->integrate(t)) {
			pForceRegistry_->deleteParticleRegistry((*it));
			onParticleDeath(*it);
		}
		
		/*if ((*it)->integrate(t)) {
			// P2
			if ((*it)->getType() >= 1) {
				Firework* firework = static_cast<Firework*>(*it);
				list<Particle*> p = firework->explode();
				for (auto d : p) {
					particles_.push_back(d);
				}
			}		
			onParticleDeath(*it);
		}*/
		
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

void ParticleSystem::generateForcedParticle(int type, PxShape* shape, float mass, Vector4 color, Vector3 pos, Vector3 vel, Vector3 accel, float damping, double lifeTime)
{
	part_ = new Firework(type, shape,
		mass, // Mass
		color, // Color
		pos, // Pos
		vel, // Vel  
		accel, // Accel
		damping,
		lifeTime);
	particles_.push_back(part_);
	if (type != 5) {
		pForceRegistry_->addRegistry(gForceGen_, part_);
	}
	else {
		pForceRegistry_->addRegistry(pDragGen_, part_);
	}
}

void ParticleSystem::onParticleDeath(Particle* p)
{
	particles_.remove(p);
	delete p;
}

void ParticleSystem::createGenerators()
{
	// P2
	/*firework_generator_ = new UniformParticleGenerator(Vector3{ 40,40,40 }, Vector3{ 50,50,50 });
	particleGenerator_.push_back(firework_generator_);
	firework_generator_ = new GaussianParticleGenerator(Vector3{ 40,40,40 }, Vector3{ 20,20,20 });
	particleGenerator_.push_back(firework_generator_);*/

	// P3
	pDragGen_ = new ParticleDragGenerator(2, 5);
	forceGenerators_.push_back(pDragGen_);
	gForceGen_ = new GravityForceGenerator({ 0, -20.0f, 0 });
	/*gForceGen_->setGravity({ 0, -10.0f, 0 });*/
	forceGenerators_.push_back(gForceGen_);
}
