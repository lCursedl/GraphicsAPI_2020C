#pragma once
#include "Formats.h"

/**	\enum TEXTURE_BINDINGS
*	\brief Enum which contains definitions for different texture bindings.
*/
enum class TEXTURE_BINDINGS
{
	SHADER_RESOURCE = 0x01,
	RENDER_TARGET = 0x02,
	DEPTH_STENCIL = 0x04
};

/** \class CTexture
*	\brief Class which serves as an interface for both CDXTexture & COGLTexture.
* 
*	Contains only a constructor and virtual destructor.
*/
class CTexture
{
public:
	CTexture();
	virtual ~CTexture();
};

TEXTURE_BINDINGS operator | (TEXTURE_BINDINGS a, TEXTURE_BINDINGS b);

bool operator & (TEXTURE_BINDINGS a, TEXTURE_BINDINGS b);

TEXTURE_BINDINGS operator |= (TEXTURE_BINDINGS& a, TEXTURE_BINDINGS b);