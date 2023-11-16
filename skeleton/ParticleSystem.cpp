#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	pForceRegistry_ = new ParticleForceRegistry();
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

	pForceRegistry_->updateForces(t);
	list<Particle*>::iterator it = particles_.begin();
	while (it != particles_.end()) {
		auto aux = it;
		++aux;
		if ((*it)->integrate(t)) {
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
	part_ = new Particle(type, shape,
		mass, // Mass
		color, // Color
		pos, // Pos
		vel, // Vel  
		accel, // Accel
		damping,
		lifeTime);
	particles_.push_back(part_);
	switch (type) {
	case 1:
		pForceRegistry_->addRegistry(gForceGen1_, part_);
		break;
	case 2:
		gForceGen2_->setGravity(Vector3(0.0f, -17.0f, 0.0f));
		pForceRegistry_->addRegistry(gForceGen2_, part_);
		break;
	case 3:
		pForceRegistry_->addRegistry(wForceGen_, part_);
		break;
	case 4: 
		pForceRegistry_->addRegistry(whirlForceGen_, part_);
		break;
	/*case 5:
		eForceGen_->
		pForceRegistry_->addRegistry(eForceGen_, part_);
		break;*/
	default:
		break;
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
	gForceGen1_ = new GravityForceGenerator({ 0, -9.8f, 0 });
	forceGenerators_.push_back(gForceGen1_);
	gForceGen2_ = new GravityForceGenerator({ 0, -9.8f, 0 });
	forceGenerators_.push_back(gForceGen2_);
	wForceGen_ = new WindForceGenerator(10.0f, 1.0f, Vector3(0.0f, 0.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(50.0f, 100.0f, 50.0f));
	forceGenerators_.push_back(wForceGen_);
	whirlForceGen_ = new WhirlwindForceGenerator(1.0f, Vector3(20.0f, 0.0f, 20.0f), Vector3(200.0f, 100.0f, 200.0f));
	forceGenerators_.push_back(whirlForceGen_);
	eForceGen_ = new ExplosionForceGenerator(1000.0f, 100.0f, Vector3(0.0f, 30.0f, 0.0f), 343.0f, 50.0f);
	forceGenerators_.push_back(eForceGen_);
}

void ParticleSystem::explosion()
{
	for (auto p : particles_) {
		pForceRegistry_->addRegistry(eForceGen_, p);
	}
}
