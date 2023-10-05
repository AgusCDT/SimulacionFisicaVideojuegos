#ifndef SUELO_H_
#define SUELO_H_

#include "RenderUtils.hpp"
using namespace physx;

class Suelo : public RenderItem
{
private:
	PxShape* plane_ = nullptr; 
	PxTransform tr_;
	Vector4 color_;
	RenderItem* renderItem_ = nullptr;

public:
	Suelo(int x, int y, int z, Vector4 color);
	~Suelo();

};

#endif // !SUELO_H_