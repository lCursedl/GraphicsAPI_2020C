#include "COGLTexture.h"

COGLTexture::COGLTexture(){}

COGLTexture::~COGLTexture()
{
	glDeleteTextures(1, &m_iTexture);
	glDeleteRenderbuffers(1, &m_iRenderBuffer);
}
