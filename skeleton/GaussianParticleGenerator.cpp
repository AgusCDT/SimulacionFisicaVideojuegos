#include "GaussianParticleGenerator.h"
#include "Firework.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel)
{
	std_dev_pos_ = std_dev_pos;
	std_dev_vel_ = std_dev_vel;
}

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel, RigidBodyManager* rbM)
{
	std_dev_pos_ = std_dev_pos;
	std_dev_vel_ = std_dev_vel;

	rbM_ = rbM;
}

list<Particle*> GaussianParticleGenerator::generateParticles(int type) {
	list<Particle*> particles;
	switch (type)
	{
	case 1:
		return generateFirework1();
		break;
	case 2:
		return generateFirework2();
		break;
	case 3:
		return generateFireworkCircle();
		break;
	case 4:
		return generateFireworkSnowy();
		break;
	default:
		break;
	}
	return particles;
}

list<rigid_body> GaussianParticleGenerator::generateRBs(int type)
{
	list<rigid_body> rbs;
	switch (type)
	{
	case 1:
		break;
	case 2:
		return generateSemiCircle();
		break;
	default:
		break;
	}
	return rbs;
}

list<Particle*> GaussianParticleGenerator::generateFirework1() { // Fuego Artificial
	list<Particle*> particles;

	for (int i = 0; i < numParticles_; i++) {
		int rand = dAux2_(mt_);
		Vector4 Col;
		switch (rand)
		{
		case 0:
			Col = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
			break;
		case 1:
			Col = (Vector4(0.0f, 0.0f, 1.0f, 1.0f));
			break;
		case 2:
			Col = (Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		default:
			break;
		}

		particles.push_back(new Particle(0, CreateShape(PxSphereGeometry(abs(dAux1_(mt_)))),
			2.0f, // Mass
			Col, // Color
			meanPos_ + Vector3(d_(mt_), d_(mt_), d_(mt_)), // Pos
			meanVel_ + Vector3(d_(mt_) * std_dev_vel_.x, d_(mt_) * std_dev_vel_.y, d_(mt_) * std_dev_vel_.z), // Vel  
			Vector3(0.0f, -10.0f, 0.0f), // Accel
			0.9f,
			d_(mt_)));
	}

	return particles;
};

list<Particle*> GaussianParticleGenerator::generateFirework2() { // Fuego Artificial
	list<Particle*> particles;

	for (int i = 0; i < numParticles_; i++) {
		float time = d_(mt_);
		Firework* firework = new Firework(1, CreateShape(PxSphereGeometry(abs(dAux1_(mt_)))),
			2.0f, // Mass
			Vector4(0.0f, 0.0f, 1.0f, 1.0f), // Color
			meanPos_ + Vector3(d_(mt_), d_(mt_), d_(mt_)), // Pos
			meanVel_ + Vector3(d_(mt_) * std_dev_vel_.x, d_(mt_) * std_dev_vel_.y, d_(mt_) * std_dev_vel_.z), // Vel  
			Vector3(0.0f, -10.0f, 0.0f), // Accel
			0.9f,
			time);
		particles.push_back(firework);
		firework->addGenerator(this);
	}

	return particles;
};
list<Particle*> GaussianParticleGenerator::generateFireworkCircle() { // CIRCULO, utilizando el cos en x y el sin en y obtenemos una distribucion con forma circular
	list<Particle*> particles;
	setNParticles(60);
	for (int i = 0; i < numParticles_; i++) {

		float time = d_(mt_);

		float a = 2.0f * (3.14159) * d_(mt_);
		float x = 30.0f * cos(a);
		float y = 30.0f * sin(a);
		Vector3 pos = meanPos_ + Vector3(x, y, 0);

		Vector3 distToCenter = pos - meanPos_;

		particles.push_back(new Particle(0, CreateShape(PxSphereGeometry(1.0f)),
			2.0f, // Mass
			Vector4(0.0f, 1.0f, 1.0f, 1.0f), // Color
			pos, // Pos
			meanVel_ + distToCenter, // Vel  
			Vector3(0.0f, -10.0f, 0.0f), // Accel
			0.9f,
			time));
	}

	return particles;
}
list<Particle*> GaussianParticleGenerator::generateFireworkSnowy() // NEVADA
{
	list<Particle*> particles;
	setNParticles(500);
	changeDistribution(2, 8);
	for (int i = 0; i < numParticles_; i++) {

		float time = d_(mt_);

		particles.push_back(new Particle(0, CreateShape(PxSphereGeometry(1.0f)),
			0.2f, // Mass
			Vector4(1.0f, 1.0f, 1.0f, 0.5f), // Color
			Vector3(meanPos_ + Vector3(d_(mt_) * std_dev_pos_.x, d_(mt_), d_(mt_) * std_dev_pos_.z)), // Pos
			Vector3(d_(mt_), -d_(mt_), 0), // Vel
			Vector3(0.0f, -10.0f, 0.0f), // Accel
			0.25f,
			time));
	}

	return particles;
}

list<rigid_body> GaussianParticleGenerator::generateSemiCircle()
{
	
	list<rigid_body> rbs;
	setNParticles(5);
	for (int i = 0; i < numParticles_; i++) {

		float time = d_(mt_);

		float a = -(3.14159) * d_(mt_);
		float x = 6.0f * cos(a);
		float y = 6.0f * sin(a);
		Vector3 pos = meanPos_ + Vector3(x, y, 0);

		Vector3 distToCenter = pos - meanPos_;

		rigid_body rb = rbM_->addRigidDynamic(1, Vector3(2.0, 0.2, 2.0), Vector4(1.0, 0.2, 0.0, 1.0), pos,
			meanVel_ + distToCenter, Vector3(0, 0, 0), 0.03, 7, 3);
	}

	return rbs;
}
