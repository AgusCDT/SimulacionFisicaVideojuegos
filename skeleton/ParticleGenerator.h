#ifndef PARTICLE_GENERATOR_H_
#define PARTICLE_GENERATOR_H_

#include "Particle.h"
#include <list>

using namespace std;

class ParticleGenerator
{
protected:
	Vector3 meanPos_;
	Vector3 meanVel_;
	double genProbability_ = 0.3; // Si está a 1.0 (100%)
	int numParticles_ = 20;
	Particle* model_ = nullptr;

	mt19937 mt_;
	uniform_real_distribution<double> u_{ 0,1 };
	string name_;

public:
	virtual list<Particle*> generateParticles(int type) = 0;
	virtual list<rigid_body> generateRBs(int type) = 0;

	inline void setOrigin(const Vector3& p) { meanPos_ = p; }
	inline void setMeanVelocity(const Vector3& v) { meanVel_ = v; }
	inline Vector3 getMeanVelocity() const { return meanVel_; }
	inline void setMeanDuration(double new_duration) { model_->timer_ = new_duration; }

	inline void setParticle(Particle* p, bool modify_pos_vel = true) {
		delete model_;
		if (modify_pos_vel) {
			meanVel_ = p->getVel();
		}
		model_->setPos({ -1000.0f, -1000.0f, -1000.0f });
	}
	inline void setNParticles(int n_p) { numParticles_ = n_p; }
};

#endif // !PARTICLE_GENERATOR_