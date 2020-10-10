#include "COGLVertexShader.h"

COGLVertexShader::COGLVertexShader()
{
	m_VertexShader = 0;
}

COGLVertexShader::~COGLVertexShader()
{
}

void COGLVertexShader::clear()
{
	glDeleteShader(m_VertexShader);
}
