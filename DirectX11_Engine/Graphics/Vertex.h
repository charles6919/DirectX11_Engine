#pragma once
#include <DirectXMath.h>

struct Vertex
{
	Vertex()
		:pos(0.0f, 0.0f, 0.0f), color(1.0f, 1.0f, 1.0f) {}

	Vertex(float x, float y, float z, float r, float g, float b)
		:pos(x,y,z), color(r,g,b) {}

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 color;
};

struct VertexUV
{
	VertexUV()
		:pos(0.0f, 0.0f, 0.0f), uv(0.0f, 0.0f){}

	VertexUV(float x, float y, float z, float u, float v)
		:pos(x,y,z), uv(u,v) {}

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 uv;
};