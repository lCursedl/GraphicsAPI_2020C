#pragma once

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