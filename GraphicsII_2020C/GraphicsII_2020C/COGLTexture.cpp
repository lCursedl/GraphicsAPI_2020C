#include "COGLTexture.h"

COGLTexture::COGLTexture()
{
	m_iTexture = 0;
	m_iFramebuffer = 0;
}

COGLTexture::~COGLTexture()
{
	if (m_iTexture != 0)
	{
		glDeleteTextures(1, &m_iTexture);
	}
	if (m_iFramebuffer != 0)
	{
		glDeleteFramebuffers(1, &m_iFramebuffer);
	}
}