#pragma once
#include "CShader.h"
#include <glad/glad.h>

class COGLPixelShader :
    public CPixelShader
{
public:
    COGLPixelShader();
    ~COGLPixelShader();

private:
    unsigned int m_PS;

    friend class COGLGraphicsAPI;
};