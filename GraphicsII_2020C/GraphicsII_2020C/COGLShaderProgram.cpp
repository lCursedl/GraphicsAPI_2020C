#include "COGLShaderProgram.h"
#include "COGLVertexShader.h"
#include "COGLPixelShader.h"

COGLShaderProgram::COGLShaderProgram(){}

COGLShaderProgram::~COGLShaderProgram()
{
	glDeleteProgram(m_Program);
}

void COGLShaderProgram::setVertexShader(CVertexShader* vertexShader)
{
	if (m_Program == 0)
	{
		return;
	}

	COGLVertexShader* vs = dynamic_cast<COGLVertexShader*>(vertexShader);

	if (!vs)
	{
		return;
	}

	if (vs->m_VertexShader == 0)
	{
		return;
	}
	glAttachShader(m_Program, vs->m_VertexShader);
	m_pVertexShader = vertexShader;
}

void COGLShaderProgram::setPixelShader(CPixelShader* pixelShader)
{
	if (m_Program == 0)
	{
		return;
	}

	COGLPixelShader* ps = dynamic_cast<COGLPixelShader*>(pixelShader);

	if (!ps)
	{
		return;
	}

	if (ps->m_PS == 0)
	{
		return;
	}
	glAttachShader(m_Program, ps->m_PS);
	m_pPixelShader = pixelShader;
}

void COGLShaderProgram::linkProgram()
{
	glLinkProgram(m_Program);
	int result;
	char log [512];
	glGetProgramiv(m_Program, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(m_Program, 512, 0, log);
	}
	glDetachShader(m_Program,
		dynamic_cast<COGLVertexShader*>(m_pVertexShader)->m_VertexShader);
	glDetachShader(m_Program,
		dynamic_cast<COGLPixelShader*>(m_pPixelShader)->m_PS);
}