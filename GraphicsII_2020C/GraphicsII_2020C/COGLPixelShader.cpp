#include "COGLPixelShader.h"

COGLPixelShader::COGLPixelShader()
{
	m_PS = 0;
}

COGLPixelShader::~COGLPixelShader()
{
	glDeleteShader(m_PS);
}