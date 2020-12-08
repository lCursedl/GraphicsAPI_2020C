#include "COGLSamplerState.h"
#include <glad/glad.h>

COGLSamplerState::COGLSamplerState()
{
	m_Sampler = 0;
}

COGLSamplerState::~COGLSamplerState()
{
	if (m_Sampler != 0)
	{
		glDeleteSamplers(1, &m_Sampler);
	}
}