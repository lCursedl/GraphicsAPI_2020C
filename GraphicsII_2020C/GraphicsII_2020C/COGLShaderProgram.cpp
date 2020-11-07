#include "COGLShaderProgram.h"
#include "COGLVertexShader.h"
#include "COGLPixelShader.h"

COGLShaderProgram::COGLShaderProgram()
{
	m_pVertexShader = new COGLVertexShader();
	m_pPixelShader = new COGLPixelShader();
}

COGLShaderProgram::~COGLShaderProgram()
{
	glDeleteProgram(m_Program);
}