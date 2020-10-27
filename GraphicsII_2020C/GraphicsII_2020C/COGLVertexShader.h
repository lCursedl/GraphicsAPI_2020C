#pragma once
#include "CShader.h"
#include <glad/glad.h>
class COGLVertexShader :
    public CVertexShader
{
public:
    COGLVertexShader();
    ~COGLVertexShader();

private:
    unsigned int m_VertexShader;

    friend class COGLGraphicsAPI;
};