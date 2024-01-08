#include "Firework.h"
#include "ParticleGenerator.h"

Firework::Firework(PxPhysics* gPhysics, PxScene* gScene)
{
	gPhysics_ = gPhysics;
	gScene_ = gScene;
}

list<Particle*> Firework::explode()
{
	gens_.front()->setOrigin(tr_.p);
	gens_.front()->setMeanVelocity(vel_);
	return gens_.front()->generateParticles(type_);
}

list<rigid_body> Firework::explodeRB(rigid_body rb)
{
	if (gens_.size() < 200) {
		gens_.front()->setOrigin(rb.body_->getGlobalPose().p);
		gens_.front()->setMeanVelocity(rb.body_->getLinearVelocity());
		return gens_.front()->generateRBs(rb.typeRB_);
	}
}

void Firework::addGenerator(ParticleGenerator* p)
{
	gens_.push_back(p);
}

rigid_body Firework::createFireworkRB(Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime)
{
	rigid_body rb;
	PxRigidDynamic* new_solid;
	new_solid = gPhysics_->createRigidDynamic(PxTransform(pos));
	new_solid->setLinearVelocity(velocity);
	new_solid->setAngularVelocity(angularvelocity);
	rb.shape_ = CreateShape(PxSphereGeometry(dim.x));
	new_solid->attachShape(*rb.shape_);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, density);

	gScene_->addActor(*new_solid);

	// Pintar actor dinámico
	rb.renderItem_ = new RenderItem(rb.shape_, new_solid, color);

	rb.body_ = new_solid;
	rb.lifeTime_ = lifetime;
	rb.typeRB_ = 1;
	
	return rb;
}
