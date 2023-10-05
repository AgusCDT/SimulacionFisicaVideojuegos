#include "Diana.h"

Diana::Diana(int x, int y, int z, Vector4 color) {
	tr_.p = GetCamera()->getTransform().p - Vector3(50.0f, 0.0f, 50.0f);
	tr_.q = { 0, 0, 0, 0 };
	box_ = CreateShape(PxBoxGeometry(x/2, y/2, z/2));

	renderItem_ = new RenderItem(box_, &tr_, color);
}
