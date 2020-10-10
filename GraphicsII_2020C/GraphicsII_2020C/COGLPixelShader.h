#pragma once
#include "CShader.h"
#include <glad/glad.h>

class COGLPixelShader :
    public CPixelShader
{
public:
    COGLPixelShader();
    ~COGLPixelShader();

    void clear()                override;

    unsigned int m_PS;
};