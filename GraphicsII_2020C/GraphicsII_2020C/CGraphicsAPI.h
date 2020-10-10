#pragma once                                                                             
#include <windows.h>
#include "CRTV.h"
#include "CTexture.h"
#include "CShader.h"
#include "CBuffer.h"

class CGraphicsAPI
{
public:

	virtual bool init(HWND window) = 0;
	virtual bool createTexture(CTexture* tex, CRTV* rtv = nullptr) = 0;
	virtual bool createRTV(CRTV * rtv, CTexture* tex = nullptr) = 0;
	virtual void setBackBuffer() = 0;
	virtual void setRTV(CRTV * rtv) = 0;
	virtual bool compileAndCreateVertexShader(WCHAR* filename,
		CVertexShader* shader,
		LPCSTR entryPoint,
		LPCSTR shaderModel) = 0;
	virtual bool compileAndCreatePixelShader(WCHAR* filename,
		CPixelShader* shader,
		LPCSTR entryPoint,
		LPCSTR shaderModel) = 0;
	virtual void setViewport(int width, int height) = 0;
	virtual bool createBuffer(const void* data, CBuffer* buffer) = 0;
};