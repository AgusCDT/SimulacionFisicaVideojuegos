#ifndef PARTICLE_GENERATOR_H_
#define PARTICLE_GENERATOR_H_

#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>
#include <random>

using namespace physx;
using namespace std;

class ParticleGenerator
{
protected:
	Vector3 meanPos_;
	Vector3 meanVel_;
	double genProbability_ = 1.0; // Si está a 1.0 (100%)
	int numParticles_ = 20;
	Particle* model_ = nullptr;

	mt19937 mt_;
	uniform_real_distribution<double> u_{ 0,1 };
	string name_;

public:
	void setParticle(Particle* model);
	virtual list<Particle*> generateParticles(ParticleType type) = 0;

	inline void setOrigin(const Vector3& p) { meanPos_ = p; }
	inline void setMeanVelocity(const Vector3& v) { meanVel_ = v;}
	inline Vector3 getMeanVelocity() const { return meanVel_; }
	inline void setMeanDuration(double new_duration) { model_->setTimer(new_duration); }

	inline void setParticle(Particle* p, bool modify_pos_vel = true) {
		delete model_;
		/*model_ = p->clone();*/
		if (modify_pos_vel) {
			/*meanPos_ = p->_pose.p;*/
			meanVel_ = p->getVel();
		}
		model_->setPos({ -1000.0f, -1000.0f, -1000.0f });
	}
	inline void setNParticles(int n_p) { numParticles_ = n_p; }
};

#endif // !PARTICLE_GENERATOR_



