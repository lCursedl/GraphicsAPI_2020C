#include "COGLTexture.h"

COGLTexture::COGLTexture()
{
	m_Texture = 0;
}

COGLTexture::~COGLTexture(){}

void COGLTexture::init(
	unsigned int Width,
	unsigned int Height,
	unsigned int Miplevels,
	unsigned int ArraySize,
	unsigned int Format,
	unsigned int Count,
	unsigned int Quality,
	unsigned int Usage,
	unsigned int Flags,
	unsigned int CPUAccessFlags,
	unsigned int MiscFlags)
{
	glGenTextures(1, &m_Texture);
	m_Width = Width;
	m_Height = Height;
}

void COGLTexture::clear()
{
	glDeleteTextures(1, &m_Texture);
}
