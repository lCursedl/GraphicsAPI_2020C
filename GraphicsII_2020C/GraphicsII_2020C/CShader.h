#pragma once

enum SHADER_TYPE
{
	VERTEX_SHADER,
	PIXEL_SHADER
};

class CVertexShader
{
public:
	CVertexShader() {}
	~CVertexShader() {}

	virtual void clear() = 0;
};

class CPixelShader
{
public:
	CPixelShader() {}
	~CPixelShader() {}

	virtual void clear() = 0;
};