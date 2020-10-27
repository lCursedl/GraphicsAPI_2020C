#pragma once
#include "CTexture.h"
#include <glad/glad.h>

class COGLTexture :
    public CTexture
{
public:
    COGLTexture();
    ~COGLTexture();

private:

    unsigned int m_iTexture;
    unsigned int m_iRenderBuffer;

    friend class COGLGraphicsAPI;
};