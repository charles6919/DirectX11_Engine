#pragma once
#include <DirectXMath.h>

struct Vertex2D
{
	Vertex2D() {}
	Vertex2D(float x, float y)
		:pos(x,y){}

	DirectX::XMFLOAT2 pos;
};