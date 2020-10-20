#pragma once                                                                             
#include <windows.h>
#include "CRTV.h"
#include "CTexture.h"
#include "CShader.h"
#include "CBuffer.h"
#include "CShaderProgram.h"

#include <string>

class CGraphicsAPI
{
public:

	virtual bool init(HWND window) = 0;

	//DEVICE
	
	virtual CTexture* createTexture(int width, int height) = 0;	
	virtual CShaderProgram* createShaderProgram(std::wstring vsfile,
		std::wstring psfile) = 0;
	virtual CBuffer* createBuffer(const void* data,
		unsigned int size,
		BUFFER_TYPE type) = 0;
	//DEVICE CONTEXT

	virtual void setBackBuffer() = 0;
	virtual void setViewport(int width, int height) = 0;
	virtual void draw(unsigned int indices) = 0;
	virtual void setShaders(CShaderProgram* program) = 0;
	virtual void clearBackBuffer(float red, float green, float blue) = 0;
};