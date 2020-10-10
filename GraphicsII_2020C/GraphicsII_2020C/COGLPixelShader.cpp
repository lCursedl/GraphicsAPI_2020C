#include "COGLPixelShader.h"

COGLPixelShader::COGLPixelShader()
{
	m_PS = 0;
}

COGLPixelShader::~COGLPixelShader(){}

void COGLPixelShader::clear()
{
	glDeleteShader(m_PS);
}
