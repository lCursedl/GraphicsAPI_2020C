#pragma once
#include "CTexture.h"
#include <glad/glad.h>

class COGLTexture :
    public CTexture
{
public:
    COGLTexture();
	void clear()                override;

    unsigned int m_iTexture;
    unsigned int m_iRenderBuffer;
};