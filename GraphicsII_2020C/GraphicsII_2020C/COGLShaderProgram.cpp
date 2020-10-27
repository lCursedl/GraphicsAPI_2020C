#include "COGLShaderProgram.h"

COGLShaderProgram::COGLShaderProgram(){}

COGLShaderProgram::~COGLShaderProgram()
{
	glDeleteProgram(m_Program);
}