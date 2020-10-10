#pragma once
#include "CTexture.h"
#include <glad/glad.h>

class COGLTexture :
    public CTexture
{
public:
    COGLTexture();
    ~COGLTexture();

	void init(
		unsigned int Width,
		unsigned int Height,
		unsigned int Miplevels = 0,
		unsigned int ArraySize = 0,
		unsigned int Format = 0,
		unsigned int Count = 0,
		unsigned int Quality = 0,
		unsigned int Usage = 0,
		unsigned int Flags = 0,
		unsigned int CPUAccessFlags = 0,
		unsigned int MiscFlags = 0);

	void clear();

    unsigned int m_Texture;
	unsigned int m_Width;
	unsigned int m_Height;
};