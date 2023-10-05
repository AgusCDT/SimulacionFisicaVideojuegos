#include "Suelo.h"

Suelo::Suelo(int x, int y, int z, Vector4 color) {
	tr_.p = GetCamera()->getTransform().p - Vector3(0.0f, 10.0f, 0.0f);
	tr_.q = { 0, 0, 0, 0 };
	plane_ = CreateShape(PxBoxGeometry(x / 2, y / 2, z / 2));

	renderItem_ = new RenderItem(plane_, &tr_, color);
}
