#pragma once

/** \enum SHADER_TYPE
*	\brief Enum which contains definitions for different shader types
*/
enum SHADER_TYPE
{
	VERTEX_SHADER,
	PIXEL_SHADER
};

/**	\class CVertexShader
*	\brief Class which serves as an interface for both CDXVertexShader & COGLVertexShader.
* 
*	Contains only a constructor and virtual destructor.
*/
class CVertexShader
{
public:
	CVertexShader() {}
	virtual ~CVertexShader() {}
};

/**	\class CPixelShader
*	\brief Class which serves as an interface for both CDXPixelShader & COGLPixelShader.
*
*	Contains only a constructor and virtual destructor.
*/
class CPixelShader
{
public:
	CPixelShader() {}
	virtual ~CPixelShader() {}
};