#include "UniformParticleGenerator.h"


UniformParticleGenerator::UniformParticleGenerator(Vector3 vel_width, Vector3 pos_width)
{
	vel_width_ = vel_width;
	pos_width_ = pos_width;
}

list<Particle*> UniformParticleGenerator::generateParticles(ParticleType type)
{

	list<Particle*> particles;

	for (int i = 0; i < numParticles_; i++) {
		
		float time = dAux_(mt_);
		meanPos_ = GetCamera()->getTransform().p;
		particles.push_back(new Particle(type, CreateShape(PxSphereGeometry(0.1)),
			2.0f, // Mass
			Vector4(1.0f, 0.4f, 0.2f, 1.0f), // Color
			Vector3(meanPos_ + Vector3(d_(mt_) * pos_width_.x, d_(mt_) * pos_width_.y, d_(mt_) * pos_width_.z)), // Pos
			Vector3(0, d_(mt_) * vel_width_.y, 0), // Vel  
			Vector3(0.0f, -1.0f, 0.0f), // Accel
			0.9f,
			time));
	}

	return particles;

}
