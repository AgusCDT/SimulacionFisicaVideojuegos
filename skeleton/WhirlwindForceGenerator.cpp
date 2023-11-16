#include "WhirlwindForceGenerator.h"

WhirlwindForceGenerator::WhirlwindForceGenerator(const float K, Vector3 origin, Vector3 size) : WindForceGenerator(K, 0, {0,0,0}, origin, size)
{
	tr_.p = Vector3(origin.x, origin.y, origin.z);
	tr_.q = { 0, 0, 0, 0 };
	cube_ = CreateShape(PxBoxGeometry(size.x, size.y, size.z));

	/*renderItem_ = new RenderItem(cube_, &tr_, Vector4(1.0f, 1.0f, 0.0f, 0.5f));*/
}

void WhirlwindForceGenerator::updateForce(Particle* p, double t)
{
	if (withinBox(p)) {
		if (fabs(p->getInverseMass()) < 1e-10) {
			return;
		}

		Vector3 pos = p->getPos();
		windVel_ = k1_ * Vector3((pos.z - origin_.z), 50 - (pos.y - origin_.y), -pos.x - origin_.x); // Vector torbellino(cambiando el signo de x y z gira hacia un lado o a otro)
		Vector3 v = p->getVel();
		Vector3 diffVel = windVel_- v; // Diferencia de velocidad
		Vector3 dragF;
		dragF = k1_ * diffVel + k2_ * diffVel.magnitude() * diffVel;
		p->addForce(dragF);
	}
}

bool WhirlwindForceGenerator::withinBox(Particle* p)
{
	Vector3 pos = p->getPos();
	if ((pos.x >= origin_.x - size_.x && pos.x <= origin_.x + size_.x) &&
		(pos.y >= origin_.y - size_.y && pos.y <= origin_.y + size_.y) &&
		(pos.z >= origin_.z - size_.z && pos.z <= origin_.z + size_.z)) {
		return true;
	}
	else {
		cout << "Out" << endl;
		return false;
	}
}
