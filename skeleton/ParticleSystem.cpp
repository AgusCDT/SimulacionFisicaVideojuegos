#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	pForceRegistry_ = new ParticleForceRegistry();
	createGenerators();
}

ParticleSystem::~ParticleSystem()
{
	particles_.clear();
}

void ParticleSystem::update(double t)
{
	if (gameOver_ == true && generaFirework_ == true) {
		generateTracaFinal();
		generaFirework_ = false;
	}
	
	pForceRegistry_->updateForces(t);

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
					pForceRegistry_->addRegistry(gForceGen1_, d);
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

void ParticleSystem::generateTracaFinal()
{
	generateFirework(2, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.0f, 0.0f, 1.0f), // Color
		Vector3(0, 2, -80),
		Vector3(0, 1, 0) * 40, // Vel  
		Vector3(0.0f, -10.0f, 0.0f), // Accel
		0.9f,
		3.0f);
	generateFirework(2, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.0f, 0.0f, 1.0f), // Color
		Vector3(60, 2, -130),
		Vector3(0, 1, 0) * 40, // Vel  
		Vector3(0.0f, -10.0f, 0.0f), // Accel
		0.9f,
		3.0f);
	generateFirework(2, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.0f, 0.0f, 1.0f), // Color
		Vector3(-40, 2, -100),
		Vector3(0, 1, 0) * 40, // Vel  
		Vector3(0.0f, -10.0f, 0.0f), // Accel
		0.9f,
		3.0f);
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
	particleGenerator_.push_back(firework_generator_);*/
	firework_generator_ = new GaussianParticleGenerator(Vector3{ 40,40,40 }, Vector3{ 20,20,20 });
	particleGenerator_.push_back(firework_generator_);

	// P3
	gForceGen1_ = new GravityForceGenerator({ 0, -9.8f, 0 });
	forceGenerators_.push_back(gForceGen1_);
	wForceGen_ = new WindForceGenerator(10.0f, 1.0f, Vector3(0.0f, 10.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(50.0f, 100.0f, 50.0f));
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
	// Then one spring with one fixed side
	Particle* p3 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 1.0f, 0.0f, 1.0f), // Color
		Vector3(5.0f, 20.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);particles_.push_back(p3);
	f3 = new AnchoredSpringFG(500, 10, { 0, 20, 0});
	pForceRegistry_->addRegistry(f3, p3);
	
	/*p3->addForce({ 1000, 0, 0 });*/
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

	pForceRegistry_->addRegistry(wForceGen_, p2);

	particles_.push_back(p1);
	particles_.push_back(p2);
}

void ParticleSystem::generateElasticBand()
{
	// First one standard spring uniting 2 particles
	Particle* p1 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.0f, 0.0f, 1.0f), // Color
		Vector3(-10.0f, 0.0f, -10.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	Particle* p2 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 1.0f, 0.0f, 1.0f), // Color
		Vector3(10.0f, 0.0f, -10.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	ElasticForceGenerator* f1 = new ElasticForceGenerator(10, 5, p2);
	pForceRegistry_->addRegistry(f1, p1);
	ElasticForceGenerator* f2 = new ElasticForceGenerator(10, 5, p1);
	pForceRegistry_->addRegistry(f2, p2);
	particles_.push_back(p1);
	particles_.push_back(p2);
}

void ParticleSystem::generateSlinky()
{
	Particle* p1 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 1.0f, 0.0f, 1.0f), // Color
		Vector3(20.0f, 100.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	Particle* p2 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.8f, 0.0f, 1.0f), // Color
		Vector3(20.0f, 90.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	Particle* p3 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.6f, 0.0f, 1.0f), // Color
		Vector3(20.0f, 80.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	Particle* p4 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.4f, 0.0f, 1.0f), // Color
		Vector3(20.0f, 70.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	Particle* p5 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.2, 0.0f, 1.0f), // Color
		Vector3(20.0f, 60.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	Particle* p6 = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f, // Mass
		Vector4(1.0f, 0.0f, 0.0f, 1.0f), // Color
		Vector3(20.0f, 50.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	
	SpringForceGenerator* f1 = new SpringForceGenerator(10, 1, p2);
	SpringForceGenerator* f2 = new SpringForceGenerator(10, 1, p1);
	SpringForceGenerator* f3 = new SpringForceGenerator(100, 5, p3);
	SpringForceGenerator* f4 = new SpringForceGenerator(10, 1, p4);
	SpringForceGenerator* f5 = new SpringForceGenerator(100, 5, p5);
	SpringForceGenerator* f6 = new SpringForceGenerator(10, 1, p6);

	pForceRegistry_->addRegistry(f1, p1);
	pForceRegistry_->addRegistry(f2, p2);

	pForceRegistry_->addRegistry(f3, p2);
	pForceRegistry_->addRegistry(f2, p3);

	pForceRegistry_->addRegistry(f4, p3);
	pForceRegistry_->addRegistry(f3, p4);

	pForceRegistry_->addRegistry(f5, p4);
	pForceRegistry_->addRegistry(f4, p5);

	pForceRegistry_->addRegistry(f6, p5);
	pForceRegistry_->addRegistry(f5, p6);

	/*pForceRegistry_->addRegistry(gForceGen1_, p6);*/

	particles_.push_back(p1);
	particles_.push_back(p2);
	particles_.push_back(p3);
	particles_.push_back(p4);
	particles_.push_back(p5);
	particles_.push_back(p6);
}

void ParticleSystem::generateBuoyancyDemo()
{
	Particle* p1 = new Particle(1, CreateShape(PxBoxGeometry(20, 0.1, 20)), // Superficie del agua
		2.0f, // Mass
		Vector4(0.0f, 0.0f, 1.0f, 1.0f), // Color
		Vector3(30.0f, 10.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	Particle* p2 = new Particle(1, CreateShape(PxBoxGeometry(5, 5, 5)), // Objeto que flota
		50.0f, // Mass
		Vector4(0.0f, 1.0f, 0.0f, 1.0f), // Color
		Vector3(30.0f, 20.0f, 0.0f), // Pos
		Vector3(0.0f, 0.0f, 0.0f), // Vel  
		Vector3(0.0f, 0.0f, 0.0f), // Accel
		0.85f,
		30.0f);
	GravityForceGenerator* g1 = new GravityForceGenerator({ 0, -9.8f, 0 });
	pForceRegistry_->addRegistry(g1, p2);
	b1 = new BuoyancyForceGenerator(10, 1, 1000, p1);
	pForceRegistry_->addRegistry(b1, p2);

	particles_.push_back(p1);
	particles_.push_back(p2);
}
