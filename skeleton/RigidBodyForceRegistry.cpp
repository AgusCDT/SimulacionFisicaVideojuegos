#include "RigidBodyForceRegistry.h"

void RigidBodyForceRegistry::updateForces(double duration)
{
	for (auto it = begin(); it != end(); it++) {
		it->first->updateForce(it->second, duration);
	}
}

void RigidBodyForceRegistry::addRegistry(ForceGenerator* fg, rigid_body rb)
{
	insert(FRrigidbody(fg, rb));
}

void RigidBodyForceRegistry::deleteRigidBodyRegistry(rigid_body rb)
{
	auto it = begin();
	while (it != end()) {
		if (it->second.body_ != rb.body_) {
			it++;
		}
		else {
			it = this->erase(it);
		}
	}
}