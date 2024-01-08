#include "RigidBodyManager.h"
#include <thread>
#include <PxPhysicsAPI.h>

RigidBodyManager::RigidBodyManager(PxPhysics* gPhysics, PxScene* gScene)
{
	gPhysics_ = gPhysics;
	gScene_ = gScene;

	rbForceRegistry_ = new RigidBodyForceRegistry();
	createGenerators();
	createScenario();

	numRBs_ = 0;

	timeBunker1_ = 0;
	timeBunker2_ = 0;
	timeBunker3_ = 0;
	
	platillosDestruidos_ = 0;
	matchTimer_ = 0;
}

RigidBodyManager::~RigidBodyManager()
{
	deleteRBs();
	delete rbForceRegistry_;
}

void RigidBodyManager::createGenerators()
{
	firework_generator_ = new GaussianParticleGenerator(Vector3{ 40,40,40 }, Vector3{ 20,20,20 }, this);
	particleGenerator_.push_back(firework_generator_);

	gForceGen_ = new GravityForceGenerator({ 0, 100.0f, 0 });
	whirlForceGen_ = new WhirlwindForceGenerator(0.1f, Vector3(20.0f, 0.0f, 20.0f), Vector3(200.0f, 100.0f, 200.0f));
	eForceGen_ = new ExplosionForceGenerator(1000.0f, 100.0f, Vector3(10.0f, 30.0f, 0.0f), 343.0f, 50.0f);
	wForceGen_ = new WindForceGenerator(1.0f, 1.0f, Vector3(0.0f, 5.0f, 0.0f), Vector3(60, 2, -130), Vector3(10.0f, 50.0f, 10.0f));
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

rigid_body RigidBodyManager::addRigidDynamic(int shape, Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime, int type)
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
	rb.typeRB_ = type;
	modifyInertiaTensor(rb, 2.0, 0.2, 2.0, shape);
	rigid_bodies_.push_back(rb);
	numRBs_++;
	return rb;
}

rigid_body RigidBodyManager::addRigidDynamicShot(int shape, Vector3 dim, Vector4 color, Vector3 pos, Vector3 velocity, Vector3 angularvelocity, float density, double lifetime)
{
	if (timeToShoot_ > 0.5) {
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
		sh.typeRB_ = 0;
		modifyInertiaTensor(sh, dim.x, dim.y, dim.z, shape);
		shots_.push_back(sh);
		numRBs_++;
		timeToShoot_ = 0;
		return sh;
	}		
}

void RigidBodyManager::update(double t)
{
	if (platillosDestruidos_ > PLATILLOS_TO_WIN) {
		deleteRBs();
	}
	else {		
		updateDynamic(t);
		updateDynamicShot(t);
	}
}

void RigidBodyManager::updateDynamic(double t)
{
	matchTimer_ += t;
	if (numRBs_ < MAX_RBS) {
		generatePlatos(t);
		rbForceRegistry_->updateForces(t);
	}
	for (auto it = rigid_bodies_.begin(); it != rigid_bodies_.end();) {
		it->time_ += t;
		if (it->typeRB_ != 4) {
			for (auto shot : shots_)
				if (shot.body_->getWorldBounds().intersects(it->body_->getWorldBounds())) {
					destroy = true;
					platillosDestruidos_++;
				}
		}

		if ((it)->typeRB_ == 3) {
			it->body_->addForce(Vector3(0, 1.9, 0));
		}
		if (destroy == true || it->time_ >= it->lifeTime_) {
			if ((it)->typeRB_ == 2) {
				firework_generator_->setOrigin(it->body_->getGlobalPose().p);
				firework_generator_->setMeanVelocity(it->body_->getLinearVelocity());
				firework_generator_->generateRBs(2);
			}
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
}

void RigidBodyManager::updateDynamicShot(double t)
{
	timeToShoot_ += t;
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
}

void RigidBodyManager::deleteRBs()
{
	for (auto& rb : rigid_bodies_) {
		rbForceRegistry_->deleteRigidBodyRegistry(rb);
		gScene_->removeActor(*(rb.body_));
		(rb.body_)->detachShape(*(rb.shape_));
		(rb.renderItem_)->release();
		(rb.body_)->release();
	}
	rigid_bodies_.clear();
	for (auto& sh : shots_) {
		rbForceRegistry_->deleteRigidBodyRegistry(sh);
		gScene_->removeActor(*(sh.body_));
		(sh.body_)->detachShape(*(sh.shape_));
		(sh.renderItem_)->release();
		(sh.body_)->release();
	}
	shots_.clear();
}

void RigidBodyManager::generateSemiCircleOrigin()
{	
	addRigidDynamic(2, Vector3(1, 0, 0), Vector4(1.0, 0.7, 0.0, 1.0), bunkers_[2]->getGlobalPose().p - Vector3(0, 0, 6),
		Vector3(0, 25, 0), Vector3(0, 0, 0), 0.001, 3, 2);
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


void RigidBodyManager::createScenario()
{
	// Campo
	campo_ = addRigidStatic(1, Vector3(100, 0.1, 100), Vector4(0.0, 0.9, 0.2, 0.1), Vector3(0, 0, -100));
	// Búnkeres
	bunkers_[0] = addRigidStatic(1, Vector3(10, 2, 2), Vector4(0.0, 0.0, 0.0, 1.0), Vector3(0, 2, -80));
	bunkers_[1] = addRigidStatic(1, Vector3(10, 2, 2), Vector4(0.0, 0.0, 0.0, 1.0), Vector3(60, 2, -130));
	bunkers_[2] = addRigidStatic(1, Vector3(10, 2, 2), Vector4(0.0, 0.0, 0.0, 1.0), Vector3(-40, 2, -100));
	// Muelles
	Vector3 posObstacle1 = { bunkers_[2]->getGlobalPose().p.x + 10, bunkers_[2]->getGlobalPose().p.y - 4, bunkers_[2]->getGlobalPose().p.z + 20 };
	Vector3 posObstacle2 = { bunkers_[1]->getGlobalPose().p.x - 20, bunkers_[1]->getGlobalPose().p.y - 4, bunkers_[1]->getGlobalPose().p.z + 50 };
	springs_[0] = addRigidDynamic(3, Vector3(1.0, 4.0, 0), Vector4(0.0, 0.0, 0.0, 1.0), posObstacle1 + Vector3(0, 15, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.001, 1e6, 4);
	modifyInertiaTensor(springs_[0], 1, 4, 0, 3);
	springs_[1] = addRigidDynamic(3, Vector3(1.0, 4.0, 0), Vector4(0.0, 0.0, 0.0, 1.0), posObstacle2 + Vector3(0, 15, 0),
		Vector3(0, 0, 0), Vector3(0, 0, 0), 0.001, 1e6, 4);
	modifyInertiaTensor(springs_[1], 1, 4, 0, 3);
	PxRigidStatic* r = addRigidStatic(1, Vector3(10, 2, 2), Vector4(0.0, 0.0, 0.0, 1.0), Vector3(0, 2, -80));
	as1 = new AnchoredSpringFG(1, 20, posObstacle1);
	rbForceRegistry_->addRegistry(as1, springs_[0]);
	rbForceRegistry_->addRegistry(gForceGen_, springs_[0]);
	as2 = new AnchoredSpringFG(1, 20, posObstacle2);
	rbForceRegistry_->addRegistry(as2, springs_[1]);
	rbForceRegistry_->addRegistry(gForceGen_, springs_[1]);
}

void RigidBodyManager::generatePlatos(double t)
{
	timeBunker1_ += t;
	timeBunker2_ += t;
	timeBunker3_ += t;

	if (timeBunker1_ > 7) {
		rigid_body r = addRigidDynamic(1, Vector3(2.0, 0.2, 2.0), Vector4(1.0, 0.2, 0.0, 1.0), bunkers_[0]->getGlobalPose().p - Vector3(0, 0, 6),
			Vector3(0, 20, 0), Vector3(0, 0, 0), 0.01, 7, 0);
		rbForceRegistry_->addRegistry(whirlForceGen_, r);
		timeBunker1_ = rand() % 4;
	}
	if (timeBunker2_ > 9) {
		rigid_body r = addRigidDynamic(1, Vector3(2.0, 0.2, 2.0), Vector4(1.0, 0.2, 0.0, 1.0), bunkers_[1]->getGlobalPose().p - Vector3(0, 0, 6),
			Vector3(0, 0, 0), Vector3(0, 0, 0), 0.1, 7, 0);
		rbForceRegistry_->addRegistry(wForceGen_, r);
		timeBunker2_ = rand() % 7;
	}
	if (timeBunker3_ > 10) {		
		generateSemiCircleOrigin();		
		timeBunker3_ = 0;
	}		
}

string RigidBodyManager::setScoringText()
{
	return "Platillos destruidos: " + to_string(getPlatillosDestruidos());
}

string RigidBodyManager::setWinText()
{
	if (getPlatillosDestruidos() > PLATILLOS_TO_WIN) {
		gameOver_ = true;
		return "GameOver. Has tardado " + to_string((int)matchTimer_) + " segundos";		
	}
	else return "";
}

void RigidBodyManager::modifyInertiaTensor(rigid_body rb, double dimx, double dimy, double dimz, int shape)
{
	double mass = rb.body_->getMass();
	double Ixx, Iyy, Izz;
	switch (shape) {
	case 1:
		Ixx = (1 / 12) * mass * ((dimy * dimy) + (dimx * dimx));
		Iyy = (1 / 12) * mass * ((dimx * dimx) + (dimz * dimz));
		Izz = (1 / 12) * mass * ((dimx * dimx) + (dimy * dimy));
		break;
	case 2:
		Ixx = Iyy = Izz = (2/5) * mass * (dimx * dimx);
		break;
	case 3:
		Ixx = (1 / 12) * mass * (3 * (dimx * dimx) + (dimy / 2) * (dimy / 2));
		Iyy = (1 / 12) * mass * (dimx * dimx + 3 * (dimy / 2) * (dimy / 2));
		Izz = (1 / 12) * mass * (dimx * dimx + dimx * dimx);
		break;
	}
	
	rb.body_->setMassSpaceInertiaTensor(Vector3(Ixx, Iyy, Izz));
}
