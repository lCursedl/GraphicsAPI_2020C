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
	virtual ~CVertexShader() {}
};

class CPixelShader
{
public:
	CPixelShader() {}
	virtual ~CPixelShader() {}
};