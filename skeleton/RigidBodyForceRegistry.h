#ifndef RIGIDBODY_FORCE_REGISTRY_H_
#define RIGIDBODY_FORCE_REGISTRY_H_

#include <map>
#include "ForceGenerator.h"
#include <list>

typedef pair<ForceGenerator*, rigid_body> FRrigidbody;
class RigidBodyForceRegistry: public multimap<ForceGenerator*, rigid_body>
{
public:
	void updateForces(double duration);

	void addRegistry(ForceGenerator* fg, rigid_body rb);

	void deleteRigidBodyRegistry(rigid_body rb);
};
#endif // !RIGIDBODY_FORCE_REGISTRY_H_

