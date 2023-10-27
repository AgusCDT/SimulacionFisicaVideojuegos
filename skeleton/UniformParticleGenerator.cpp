#include "UniformParticleGenerator.h"
#include "Firework.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 vel_width, Vector3 pos_width)
{
	vel_width_ = vel_width;
	pos_width_ = pos_width;
}

list<Particle*> UniformParticleGenerator::generateParticles(int type)
{
	list<Particle*> particles;
	switch (type)
	{
	case 5:
	{
		return generateRain();
	}
	default:
		break;
	}

	return particles;
}

list<Particle*> UniformParticleGenerator::generateRain() { // Mediante la distribución uniforme simulamos una lluvia
	list<Particle*> particles;
	setNParticles(200);
	for (int i = 0; i < numParticles_; i++) {
		float time = dAux_(mt_);
		particles.push_back(new Particle(0, CreateShape(PxSphereGeometry(1.0f)),
			2.0f, // Mass
			Vector4(0.0f, 0.0f, 1.0f, 1.0f), // Color
			Vector3(meanPos_ + Vector3(d_(mt_) * pos_width_.x, d_(mt_) * pos_width_.y, d_(mt_) * pos_width_.z)), // Pos
			Vector3(0, -d_(mt_) * vel_width_.y, 0), // Vel  
			Vector3(0.0f, -10.0f, 0.0f), // Accel
			0.9f,
			time));
	}
	return particles;
};
