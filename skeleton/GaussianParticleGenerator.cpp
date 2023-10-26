#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel)
{
	std_dev_pos_ = std_dev_pos;
	std_dev_vel_ = std_dev_vel;
}

list<Particle*> GaussianParticleGenerator::generateParticles(ParticleType type) {
	list<Particle*> particles;

	for (int i = 0; i < numParticles_; i++) {	
		float time = dAux1_(mt_);	
		meanPos_ = GetCamera()->getTransform().p /*+ Vector3(GetCamera()->getTransform().p.x+40, 0, GetCamera()->getTransform().p.z + 40)*/;
		particles.push_back(new Particle(type, CreateShape(PxSphereGeometry(abs(dAux2(mt_)))),
			2.0f, // Mass
			Vector4(1.0f, 0.4f, 0.2f, 1.0f), // Color
			meanPos_ + Vector3(d_(mt_), d_(mt_), d_(mt_)),
			meanVel_ + Vector3(d_(mt_) * std_dev_vel_.x, d_(mt_) * std_dev_vel_.y, d_(mt_) * std_dev_vel_.z), // Vel  
			Vector3(0.0f, -1.0f, 0.0f), // Accel
			0.9f,
			time));
	}
	return particles;
}
