#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos) : SpringForceGenerator(k, resting, nullptr)
{
	other_ = new Particle(1, CreateShape(PxSphereGeometry(2.0f)),
		2.0f,
		Vector4(1.0f, 1.0f, 0.0f, 1.0f),
		anchor_pos,
		{ 0,0,0 },
		{ 0,0,0 }, 
		0, 
		1e6);
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete other_;
}
