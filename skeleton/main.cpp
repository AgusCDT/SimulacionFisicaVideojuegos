#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

//#include "Particle.h"
#include "Suelo.h"
//#include "Diana.h"
#include "ParticleSystem.h"
#include <list>
#include <iostream>

string display_text = "P2";


using namespace physx;
using namespace std;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;

#pragma region P1
//Particle* myParticle_ = nullptr; // Particula
//vector<Particle*> particles_; // CAPAR MAX DE PARTICULAS

Suelo* suelo_ = nullptr;

//Diana* diana_ = nullptr;
#pragma endregion

ParticleSystem* particleSystem_ = nullptr;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

#pragma region P1
	suelo_ = new Suelo(240, 10, 240, Vector4(0.0f, 0.0f, 0.0f, 1.0f)); // "Suelo"

	/*diana_ = new Diana(10, 10, 10, Vector4(0.0f, 0.0f, 0.0f, 1.0f));*/
#pragma endregion
	particleSystem_ = new ParticleSystem();
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
#pragma region P1
	//if (particles_.size() > 0) {
	//	for (auto e : particles_) {
	//		e->integrate(t); // Actualizamos atributos de cada particula
	//	}
	//}
#pragma endregion	

	if (particleSystem_ != nullptr) {
		particleSystem_->update(t);
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
#pragma region P1
	/*if (particles_.size() > 0) {
		for (auto e : particles_) {
			delete e;
		}
	}*/
#pragma endregion
	delete particleSystem_;
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{
#pragma region P1
		//case 'V': // PISTOL
		//{
		//	myParticle_ = new Particle(CreateShape(PxSphereGeometry(0.4)), // Shape
		//		2.0f, // Mass
		//		Vector4(1.0f, 0.4f, 0.2f, 1.0f), // Color
		//		Vector3(GetCamera()->getDir().x * 35.0f, 0.0f, GetCamera()->getDir().z * 35.0f), // Vel  // CAMBIAR A SOLO UN GetCamera()->getDir() * 35
		//		Vector3(0.0f, -1.0f, 0.0f), // Accel
		//		0.9f); // Damping
		//	particles_.push_back(myParticle_);
		//}
		//break;
		//case 'B': // ARTILLERY
		//{
		//	myParticle_ = new Particle(CreateShape(PxSphereGeometry(1.7)),
		//		200.0f,
		//		Vector4(0.0f, 1.0f, 1.0f, 1.0f),
		//		Vector3(GetCamera()->getDir().x * 40.0f, 30.0f, GetCamera()->getDir().z * 40.0f),
		//		Vector3(0.0f, -20.0f, 0.0f),
		//		0.99f);
		//	particles_.push_back(myParticle_);
		//}
		//break;
		//case 'N': // FIREBALL
		//{
		//	myParticle_ = new Particle(CreateShape(PxSphereGeometry(0.8)),
		//		1.0f,
		//		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		//		Vector3(GetCamera()->getDir().x * 10.0f, 0.0f, GetCamera()->getDir().z * 10.0f),
		//		Vector3(0.0f, 0.6f, 0.0f),
		//		0.9f);
		//	particles_.push_back(myParticle_);
		//}
		//break;
		//case 'M': // LASER
		//{
		//	myParticle_ = new Particle(CreateShape(PxSphereGeometry(0.2)),
		//		0.1f,
		//		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		//		Vector3(GetCamera()->getDir().x * 100.0f, 0.0f, GetCamera()->getDir().z * 100.0f),
		//		Vector3(0.0f, 0.0f, 0.0f),
		//		0.99f);
		//	particles_.push_back(myParticle_);
		//}
		//break;
#pragma endregion
#pragma region P2
	//case 'U': // FUEGO ARTIFICIAL
	//{
	//	particleSystem_->generateFirework(2, CreateShape(PxSphereGeometry(2.0f)),
	//		2.0f, // Mass
	//		Vector4(1.0f, 0.0f, 0.0f, 1.0f), // Color
	//		GetCamera()->getEye() + Vector3(-90, 0, -90),
	//		Vector3(0, 1, 0) * 60, // Vel  
	//		Vector3(0.0f, -10.0f, 0.0f), // Accel
	//		0.9f,
	//		4.0f);
	//}
	//break;
	//case 'I': // SNOWY
	//{
	//	particleSystem_->generateFirework(4, CreateShape(PxSphereGeometry(2.0f)),
	//		2.0f, // Mass
	//		Vector4(1.0f, 1.0f, 1.0f, 0.5f), // Color
	//		GetCamera()->getEye() + Vector3(-90, 0, -90),
	//		Vector3(0, 1, 0) * 40, // Vel  
	//		Vector3(0.0f, -10.0f, 0.0f), // Accel
	//		0.9f,
	//		4.0f);
	//}
	//break;
	//case 'O': // CIRCULO
	//{
	//	particleSystem_->generateFirework(3, CreateShape(PxSphereGeometry(2.0f)),
	//		2.0f, // Mass		
	//		Vector4(0.0f, 1.0f, 1.0f, 1.0f), // Color
	//		GetCamera()->getEye() + Vector3(-90, 0, -90),
	//		Vector3(0, 1, 0) * 10, // Vel  
	//		Vector3(0.0f, -10.0f, 0.0f), // Accel
	//		0.9f,
	//		3.5f);
	//}
	//break;
	//case 'P': // LLUVIA
	//{
	//	particleSystem_->generateFirework(5, CreateShape(PxSphereGeometry(2.0f)),
	//		2.0f, // Mass
	//		Vector4(0.0f, 0.0f, 1.0f, 1.0f), // Color
	//		GetCamera()->getEye() + Vector3(-90, 0, -90),
	//		Vector3(0, 1, 0) * 40, // Vel  
	//		Vector3(0.0f, -10.0f, 0.0f), // Accel
	//		0.9f,
	//		3.5f);
	//}
	//break;
	//default:
	//	particleSystem_->generateFirework(1, CreateShape(PxSphereGeometry(2.0f)),
	//		2.0f, // Mass
	//		Vector4(0.0f, 0.0f, 1.0f, 1.0f), // Color
	//		GetCamera()->getEye() + Vector3(-90, 0, -90),
	//		Vector3(0, 1, 0) * 40, // Vel  
	//		Vector3(0.0f, -10.0f, 0.0f), // Accel
	//		0.9f,
	//		3.5f);
	//	break;
	//}
#pragma endregion

	case 'H':// ACTIVIDAD 1, 3 partículas
	{
		// GRAVEDAD NORMAL
		particleSystem_->generateForcedParticle(1, CreateShape(PxSphereGeometry(2.0f)),
			2.0f, // Mass
			Vector4(1.0f, 0.0f, 0.0f, 1.0f), // Color
			Vector3(0.0f, 250.0f, 0.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			8.0f);
		// MAS GRAVEDAD
		particleSystem_->generateForcedParticle(2, CreateShape(PxSphereGeometry(2.0f)),
			2.0f, // Mass
			Vector4(1.0f, 1.0f, 0.0f, 1.0f), // Color
			Vector3(20.0f, 250.0f, -20.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			8.0f);
		// GRAVEDAD NORMAL Y DISTINTA MASA
		particleSystem_->generateForcedParticle(1, CreateShape(PxSphereGeometry(2.0f)),
			10.0f, // Mass
			Vector4(0.5f, 0.5f, 0.0f, 1.0f), // Color
			Vector3(40.0f, 250.0f, -40.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			8.0f);
	}
	break;
	case 'J': // ACTIVIDAD 2, VIENTO
	{
		particleSystem_->generateForcedParticle(3, CreateShape(PxSphereGeometry(2.0f)),
			2.0f, // Mass
			Vector4(0.0f, 0.0f, 1.0f, 1.0f), // Color
			Vector3(0.0f, 30.0f, 0.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			20.0f);
		particleSystem_->generateForcedParticle(3, CreateShape(PxSphereGeometry(2.0f)),
			20.0f, // Mass
			Vector4(0.0f, 0.0f, 0.5f, 1.0f), // Color
			Vector3(0.0f, 50.0f, 0.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			20.0f);
		particleSystem_->generateForcedParticle(3, CreateShape(PxSphereGeometry(2.0f)),
			20.0f, // Mass
			Vector4(0.0f, 0.3f, 1.0f, 1.0f), // Color
			Vector3(0.0f, 70.0f, 0.0f), // Pos
			Vector3(0.0f, 10.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			20.0f);
	}
	break;
	case 'K': // ACTIVIDAD 3, TORBELLINO
	{
		particleSystem_->generateForcedParticle(4, CreateShape(PxSphereGeometry(2.0f)),
			0.5f, // Mass
			Vector4(0.0f, 1.0f, 0.0f, 1.0f), // Color
			Vector3(0.0f, 0.0f, 0.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			20.0f);	
	}
	break;
	case 'L': // ACTIVIDAD 4, EXPLOSION
	{	
		particleSystem_->generateForcedParticle(5, CreateShape(PxSphereGeometry(2.0f)),
			1.0f, // Mass
			Vector4(0.0f, 1.0f, 0.0f, 1.0f), // Color
			Vector3(0.0f, 29.0f, 0.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			20.0f);	
		particleSystem_->generateForcedParticle(5, CreateShape(PxSphereGeometry(2.0f)),
			2.0f, // Mass
			Vector4(0.2f, 1.0f, 0.0f, 1.0f), // Color
			Vector3(20.0f, 20.0f, 0.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			20.0f);
		particleSystem_->generateForcedParticle(5, CreateShape(PxSphereGeometry(2.0f)),
			3.0f, // Mass
			Vector4(0.4f, 1.0f, 0.0f, 1.0f), // Color
			Vector3(0.0f, 30.0f, 30.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			20.0f);
		particleSystem_->generateForcedParticle(5, CreateShape(PxSphereGeometry(2.0f)),
			4.0f, // Mass
			Vector4(0.6f, 1.0f, 0.0f, 1.0f), // Color
			Vector3(0.0f, 10.0f, 20.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			20.0f);
		particleSystem_->generateForcedParticle(5, CreateShape(PxSphereGeometry(2.0f)),
			5.0f, // Mass
			Vector4(0.8f, 1.0f, 0.0f, 1.0f), // Color
			Vector3(15.0f, 50.0f, 0.0f), // Pos
			Vector3(0.0f, 0.0f, 0.0f), // Vel  
			Vector3(0.0f, 0.0f, 0.0f), // Accel
			0.9f,
			20.0f);
	}
	break;
	case 'M': // ACTIVIDAD 4, EXPLOSION
	{		
		particleSystem_->explosion();
	}
	break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}