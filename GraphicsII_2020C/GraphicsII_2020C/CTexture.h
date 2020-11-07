#pragma once
#include "Formats.h"

enum TEXTURE_BINDINGS
{
	SHADER_RESOURCE = 0x01,
	RENDER_TARGET = 0x02,
	DEPTH_STENCIL = 0x04
};

class CTexture
{
public:
	CTexture();
	virtual ~CTexture();
};