#include "RigidBodyManager.h"

RigidBodyManager::RigidBodyManager(PxPhysics* gPhysics, PxScene* gScene)
{
	gPhysics_ = gPhysics;
	gScene_ = gScene;

	rbForceRegistry_ = new RigidBodyForceRegistry();
	createGenerators();

	numRBs_ = 0;
}

RigidBodyManager::~RigidBodyManager()
{
	for (auto& rb : rigid_bodies_) {
		gScene_->removeActor(*(rb.body_));
	}
	delete rbForceRegistry_;
}

void RigidBodyManager::createGenerators()
{
	whirlForceGen_ = new WhirlwindForceGenerator(1.0f, Vector3(20.0f, 0.0f, 20.0f), Vector3(200.0f, 100.0f, 200.0f));
	eForceGen_ = new ExplosionForceGenerator(1000.0f, 100.0f, Vector3(10.0f, 30.0f, 0.0f), 343.0f, 50.0f);
	wForceGen_ = new WindForceGenerator(10.0f, 1.0f, Vector3(0.0f, 5.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(50.0f, 100.0f, 50.0f));
}

void RigidBodyManager::addRigidStatic(Vector3 dim, Vector4 color, Vector3 pos)
{
	if (numRBs_ < MAX_RBS) {
		PxRigidStatic* Suelo = gPhysics_->createRigidStatic(PxTransform(pos));
		PxShape* shape = CreateShape(PxBoxGeometry(dim.x, dim.y, dim.z));
		Suelo->attachShape(*shape);
		gScene_->addActor(*Suelo);
		// Pintar suelo
		RenderItem* item;
		item = new RenderItem(shape, Suelo, color);
		numRBs_++;
	}
}

void RigidBodyManager::addRigidDynamic(Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime)
{// ¡Meter distinción de forma!
	if (numRBs_ < MAX_RBS) {
		rigid_body rb;
		PxRigidDynamic* new_solid;
		new_solid = gPhysics_->createRigidDynamic(PxTransform(pos));
		new_solid->setLinearVelocity(velocity);
		new_solid->setAngularVelocity(angularvelocity);
		rb.shape_ = CreateShape(PxBoxGeometry(dim.x, dim.y, dim.z));
		new_solid->attachShape(*rb.shape_);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, density);

		gScene_->addActor(*new_solid);

		// Pintar actor dinámico
		rb.renderItem_ = new RenderItem(rb.shape_, new_solid, color);

		rb.body_ = new_solid;
		rb.lifeTime_ = lifetime;
		rigid_bodies_.push_back(rb);
		numRBs_++;
	}
}

void RigidBodyManager::update(double t)
{
	/*cout << numRBs_ << endl;*/
	rbForceRegistry_->updateForces(t);
	for (auto it = rigid_bodies_.begin(); it != rigid_bodies_.end();) {
		it->time_ += t;
		if (it->time_ >= it->lifeTime_) {
			rbForceRegistry_->deleteRigidBodyRegistry(*(it));
			gScene_->removeActor(*(it->body_));
			(it->body_)->detachShape(*(it->shape_));
			(it->renderItem_)->release();
			(it->body_)->release();
			it = rigid_bodies_.erase((it));
			numRBs_--;
		}	
		else {
			it++;
		}
	}
}

void RigidBodyManager::torbellino()
{
	for (auto rb : rigid_bodies_) {
		rbForceRegistry_->addRegistry(whirlForceGen_, rb);
	}
}

void RigidBodyManager::explosion()
{
	for (auto rb : rigid_bodies_) {
		rbForceRegistry_->addRegistry(eForceGen_, rb);
	}
}

void RigidBodyManager::viento()
{
	for (auto rb : rigid_bodies_) {
		rbForceRegistry_->addRegistry(wForceGen_, rb);
	}
}

void RigidBodyManager::generateSpringDemo1()
{
	if (numRBs_ < MAX_RBS) {
		rigid_body rb;
		PxRigidDynamic* new_solid;
		new_solid = gPhysics_->createRigidDynamic(PxTransform(Vector3(0, 40, 0)));
		new_solid->setLinearVelocity(Vector3(0, 0, 0));
		new_solid->setAngularVelocity(Vector3(0, 0, 0));
		rb.shape_ = CreateShape(PxSphereGeometry(4.0));
		new_solid->attachShape(*rb.shape_);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.01);

		gScene_->addActor(*new_solid);

		// Pintar actor dinámico
		rb.renderItem_ = new RenderItem(rb.shape_, new_solid, Vector4(1.0, 0.0, 0.0, 1.0));

		rb.body_ = new_solid;
		rb.lifeTime_ = 100;
		rigid_bodies_.push_back(rb);
		numRBs_++;
		f3 = new AnchoredSpringFG(500, 30, { 20, 20, 0 });
		rbForceRegistry_->addRegistry(f3, rb);
	}
}
