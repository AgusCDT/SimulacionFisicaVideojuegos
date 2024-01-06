#include "RigidBodyManager.h"
#include <chrono>
#include <thread>
#include <PxPhysicsAPI.h>

RigidBodyManager::RigidBodyManager(PxPhysics* gPhysics, PxScene* gScene)
{
	gPhysics_ = gPhysics;
	gScene_ = gScene;

	rbForceRegistry_ = new RigidBodyForceRegistry();
	createScenario();
	createGenerators();

	numRBs_ = 0;

	timeBunker1_ = 0;
	timeBunker2_ = 0;
	timeBunker3_ = 0;
	
	platillosDestruidos_ = 0;
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
	whirlForceGen_ = new WhirlwindForceGenerator(0.1f, Vector3(20.0f, 0.0f, 20.0f), Vector3(200.0f, 100.0f, 200.0f));
	eForceGen_ = new ExplosionForceGenerator(1000.0f, 100.0f, Vector3(10.0f, 30.0f, 0.0f), 343.0f, 50.0f);
	wForceGen_ = new WindForceGenerator(1.0f, 1.0f, Vector3(0.0f, 5.0f, 0.0f), bunkers_[1]->getGlobalPose().p, Vector3(10.0f, 50.0f, 10.0f));
}

PxRigidStatic* RigidBodyManager::addRigidStatic(int shape, Vector3 dim, Vector4 color, Vector3 pos)
{
	if (numRBs_ < MAX_RBS) {
		PxRigidStatic* Suelo = gPhysics_->createRigidStatic(PxTransform(pos));
		PxShape* shape_;
		switch (shape) {
		case 1:
			shape_ = CreateShape(PxBoxGeometry(dim.x, dim.y, dim.z));
			break;
		case 2:
			shape_ = CreateShape(PxSphereGeometry(dim.x));
			break;
		case 3:
			shape_ = CreateShape(PxCapsuleGeometry(dim.x, dim.y / 2));
			break;
		}
		
		Suelo->attachShape(*shape_);
		gScene_->addActor(*Suelo);
		// Pintar suelo
		RenderItem* item;
		item = new RenderItem(shape_, Suelo, color);
		numRBs_++;
		return Suelo;
	}
}

rigid_body RigidBodyManager::addRigidDynamic(int shape, Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime)
{	
	rigid_body rb;
	PxRigidDynamic* new_solid;
	new_solid = gPhysics_->createRigidDynamic(PxTransform(pos));
	new_solid->setLinearVelocity(velocity);
	new_solid->setAngularVelocity(angularvelocity);
	switch (shape) {
	case 1:
		rb.shape_ = CreateShape(PxBoxGeometry(dim.x, dim.y, dim.z));
		break;
	case 2:
		rb.shape_ = CreateShape(PxSphereGeometry(dim.x));
		break;
	case 3:
		rb.shape_ = CreateShape(PxCapsuleGeometry(dim.x, dim.y/2));
		break;
	}
		
	new_solid->attachShape(*rb.shape_);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, density);

	gScene_->addActor(*new_solid);

	// Pintar actor dinámico
	rb.renderItem_ = new RenderItem(rb.shape_, new_solid, color);

	rb.body_ = new_solid;
	rb.lifeTime_ = lifetime;
	rigid_bodies_.push_back(rb);
	numRBs_++;
	return rb;
}

rigid_body RigidBodyManager::addRigidDynamicShot(int shape, Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime)
{
		rigid_body sh;
		PxRigidDynamic* new_solid;
		new_solid = gPhysics_->createRigidDynamic(PxTransform(pos));
		new_solid->setLinearVelocity(velocity);
		new_solid->setAngularVelocity(angularvelocity);
		switch (shape) {
		case 1:
			sh.shape_ = CreateShape(PxBoxGeometry(dim.x, dim.y, dim.z));
			break;
		case 2:
			sh.shape_ = CreateShape(PxSphereGeometry(dim.x));
			break;
		case 3:
			sh.shape_ = CreateShape(PxCapsuleGeometry(dim.x, dim.y / 2));
			break;
		}

		new_solid->attachShape(*sh.shape_);
		PxRigidBodyExt::updateMassAndInertia(*new_solid, density);

		gScene_->addActor(*new_solid);

		// Pintar actor dinámico
		sh.renderItem_ = new RenderItem(sh.shape_, new_solid, color);

		sh.body_ = new_solid;
		sh.lifeTime_ = lifetime;
		shots_.push_back(sh);
		numRBs_++;
		return sh;
}

void RigidBodyManager::update(double t)
{
	if (numRBs_ < MAX_RBS) {
		generatePlatos(t);
		rbForceRegistry_->updateForces(t);
	}
	for (auto it = rigid_bodies_.begin(); it != rigid_bodies_.end();) {
		it->time_ += t;
		for (auto shot : shots_)
			if (shot.body_->getWorldBounds().intersects(it->body_->getWorldBounds())) {
				destroy = true;
				scoring();
			}

		if (destroy == true || it->time_ >= it->lifeTime_) {
			rbForceRegistry_->deleteRigidBodyRegistry(*(it));
			gScene_->removeActor(*(it->body_));
			(it->body_)->detachShape(*(it->shape_));
			(it->renderItem_)->release();
			(it->body_)->release();
			it = rigid_bodies_.erase((it));
			numRBs_--;
			destroy = false;
		}
		else {
			it++;
		}
	}


	for (auto it = shots_.begin(); it != shots_.end();) {
		it->time_ += t;
		if (it->time_ >= it->lifeTime_) {
			rbForceRegistry_->deleteRigidBodyRegistry(*(it));
			gScene_->removeActor(*(it->body_));
			(it->body_)->detachShape(*(it->shape_));
			(it->renderItem_)->release();
			(it->body_)->release();
			it = shots_.erase((it));
			numRBs_--;
		}
		else {
			it++;
		}
	}

	//scoring();
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

void RigidBodyManager::createScenario()
{
	// Campo
	campo_ = addRigidStatic(1, Vector3(100, 0.1, 100), Vector4(0.0, 0.9, 0.2, 0.1), Vector3(0, 0, -100));
	// Búnkeres
	bunkers_[0] = addRigidStatic(1, Vector3(10, 2, 2), Vector4(0.0, 0.0, 0.0, 1.0), Vector3(0, 2, -80));
	bunkers_[1] = addRigidStatic(1, Vector3(10, 2, 2), Vector4(0.0, 0.0, 0.0, 1.0), Vector3(60, 2, -130));
	bunkers_[2] = addRigidStatic(1, Vector3(10, 2, 2), Vector4(0.0, 0.0, 0.0, 1.0), Vector3(-40, 2, -100));

	f3 = new AnchoredSpringFG(500, 30, { bunkers_[2]->getGlobalPose().p.x, bunkers_[2]->getGlobalPose().p.y, bunkers_[2]->getGlobalPose().p.z - 10 });

}

void RigidBodyManager::collisions()
{
}

void RigidBodyManager::generatePlatos(double t)
{
	timeBunker1_ += t;
	timeBunker2_ += t;
	timeBunker3_ += t;

	if (timeBunker1_ > 3) {
		rigid_body r = addRigidDynamic(1, Vector3(1.5, 0.1, 1.5), Vector4(1.0, 0.2, 0.0, 1.0), bunkers_[0]->getGlobalPose().p - Vector3(0, 0, 6),
			Vector3(0, 20, 0), Vector3(0, 0, 0), 0.01, 7);
		rbForceRegistry_->addRegistry(whirlForceGen_, r);
		timeBunker1_ = rand() % 2;
	}
	if (timeBunker2_ > 9) {
		rigid_body r = addRigidDynamic(1, Vector3(1.5, 0.1, 1.5), Vector4(1.0, 0.2, 0.0, 1.0), bunkers_[1]->getGlobalPose().p - Vector3(0, 0, 6),
			Vector3(0, 20, 0), Vector3(0, 0, 0), 0.01, 7);
		rbForceRegistry_->addRegistry(wForceGen_, r);
		timeBunker2_ = rand() % 8;
	}
	if (numRBs_ < MAX_RBS - 1) {
		if (timeBunker3_ > 8) {
			rigid_body r = addRigidDynamic(1, Vector3(1.5, 0.1, 1.5), Vector4(1.0, 0.6, 0.0, 1.0), bunkers_[2]->getGlobalPose().p - Vector3(0, -16, 6),
				Vector3(0, 40, 0), Vector3(0, 0, 0), 0.01, 7);
			
			rbForceRegistry_->addRegistry(f3, r);			
			timeBunker3_ = rand() % 7;
		}
	}	
}

void RigidBodyManager::scoring()
{
	platillosDestruidos_++;
}
