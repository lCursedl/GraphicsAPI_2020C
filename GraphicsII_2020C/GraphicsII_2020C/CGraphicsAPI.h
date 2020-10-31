#pragma once                                                                             
#include <windows.h>
#include "CRTV.h"
#include "CTexture.h"
#include "CShader.h"
#include "CBuffer.h"
#include "CShaderProgram.h"
#include "CInputLayout.h"

#include <string>

struct Color
{
	Color(float r, float g, float b, float a)
	{
		R = r;
		G = g;
		B = b;
		A = a;
	}
	float R;
	float G;
	float B;
	float A;
};

class CGraphicsAPI
{
public:

	virtual bool init(HWND window) = 0;

	//DEVICE
	
	virtual CTexture* createTexture(int width,
		int height,
		TEXTURE_BINDINGS binding,
		TEXTURE_FORMATS format) = 0;
	virtual CShaderProgram* createShaderProgram(std::wstring vsfile,
		std::wstring psfile) = 0;
	virtual CBuffer* createBuffer(const void* data,
		unsigned int size,
		BUFFER_TYPE type) = 0;
	virtual CInputLayout* createInputLayout(CShaderProgram* program,
		LAYOUT_DESC desc) = 0;

	//DEVICE CONTEXT

	virtual void setBackBuffer() = 0;
	virtual void setViewport(int width, int height) = 0;
	virtual void drawIndexed(unsigned int indices) = 0;
	virtual void setShaders(CShaderProgram* program) = 0;
	virtual void setInputLayout(CInputLayout* layout) = 0;
	virtual void clearBackBuffer(float red, float green, float blue) = 0;
};