#ifndef DIANA_H_
#define DIANA_H_

#include "RenderUtils.hpp"
using namespace physx;

class Diana : public RenderItem
{
private:
	PxShape* box_ = nullptr;
	PxTransform tr_;
	Vector4 color_;
	RenderItem* renderItem_ = nullptr;
public:
	Diana(int x, int y, int z, Vector4 color);
	~Diana();
};
#endif // !DIANA_H_



