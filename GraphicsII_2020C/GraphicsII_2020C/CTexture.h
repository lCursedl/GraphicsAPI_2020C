#pragma once
#include "Formats.h"

/**	\enum TEXTURE_BINDINGS
*	\brief Enum which contains definitions for different texture bindings.
*/
enum TEXTURE_BINDINGS
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