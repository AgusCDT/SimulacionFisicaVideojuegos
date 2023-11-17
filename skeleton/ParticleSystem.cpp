#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	pForceRegistry_ = new ParticleForceRegistry();
	createGenerators();
}

void ParticleSystem::update(double t)
{
	pForceRegistry_->updateForces(t);

	list<Particle*>::iterator it = particles_.begin();
	while (it != particles_.end()) {
		auto aux = it;
		++aux;
		if ((*it)->integrate(t)) {
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
}

void ParticleSystem::onParticleDeath(Particle* p)
{
	pForceRegistry_->deleteParticleRegistry(p);
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
	wForceGen_ = new WindForceGenerator(10.0f, 1.0f, Vector3(0.0f, 0.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(50.0f, 100.0f, 50.0f));
	forceGenerators_.push_back(wForceGen_);
	whirlForceGen_ = new WhirlwindForceGenerator(1.0f, Vector3(20.0f, 0.0f, 20.0f), Vector3(200.0f, 100.0f, 200.0f));
	forceGenerators_.push_back(whirlForceGen_);
	eForceGen_ = new ExplosionForceGenerator(1000.0f, 100.0f, Vector3(0.0f, 30.0f, 0.0f), 343.0f, 50.0f);
	forceGenerators_.push_back(eForceGen_);
}

void ParticleSystem::gravedad(Vector3 g)
{
	for (auto p : particles_) {
		gForceGen1_->setGravity(g);
		pForceRegistry_->addRegistry(gForceGen1_, p);
	}
}

void ParticleSystem::viento()
{
	for (auto p : particles_) {
		pForceRegistry_->addRegistry(wForceGen_, p);
	}
}

void ParticleSystem::torbellino()
{
	for (auto p : particles_) {
		pForceRegistry_->addRegistry(whirlForceGen_, p);
	}
}

void ParticleSystem::explosion()
{
	for (auto p : particles_) {
		pForceRegistry_->addRegistry(eForceGen_, p);
	}
}

void ParticleSystem::generateSpringDemo1()
{
	// First one standard spring uniting 2 particles
	Particle* p1 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.0f, 0.0f, 1.0f), // Color
		Vector3(0.0f, 20.0f, 10.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	Particle* p2 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 1.0f, 0.0f, 1.0f), // Color
		Vector3(0.0f, 20.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
	pForceRegistry_->addRegistry(f1, p1);
	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);
	pForceRegistry_->addRegistry(f2, p2);
	forceGenerators_.push_back(f1);
	forceGenerators_.push_back(f2);
	particles_.push_back(p1);
	particles_.push_back(p2);
	/*p1->addForce({ 0, 0, 1000 });*/

	// Then one spring with one fixed side
	Particle* p3 = new Particle(1, CreateShape(PxBoxGeometry(10, 10, 10)),
		2.0f, // Mass
		Vector4(1.0f, 1.0f, 0.0f, 1.0f), // Color
		Vector3(0.0f, 30.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	AnchoredSpringFG* f3 = new AnchoredSpringFG(1, 10, { 10.0, 20.0, 0.0 });
	pForceRegistry_->addRegistry(f3, p3);
	forceGenerators_.push_back(f3);
	particles_.push_back(p3);
}

void ParticleSystem::generateSpringDemo2()
{
	// First one standard spring uniting 2 particles
	Particle* p1 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.0f, 0.0f, 1.0f), // Color
		Vector3(-10.0f, 20.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	Particle* p2 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 1.0f, 0.0f, 1.0f), // Color
		Vector3(10.0f, 20.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
	pForceRegistry_->addRegistry(f1, p1);
	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);
	pForceRegistry_->addRegistry(f2, p2);
	forceGenerators_.push_back(f1);
	forceGenerators_.push_back(f2);
	particles_.push_back(p1);
	particles_.push_back(p2);
}

void ParticleSystem::changeSpringK(double k)
{

}
