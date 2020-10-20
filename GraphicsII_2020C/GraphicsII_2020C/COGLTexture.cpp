#include "COGLTexture.h"

COGLTexture::COGLTexture(){}

void COGLTexture::clear()
{
	glDeleteTextures(1, &m_iTexture);
	glDeleteRenderbuffers(1, &m_iRenderBuffer);
}
