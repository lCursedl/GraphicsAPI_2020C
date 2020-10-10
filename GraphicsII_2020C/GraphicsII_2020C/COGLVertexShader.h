#pragma once
#include "CShader.h"
#include <glad/glad.h>
class COGLVertexShader :
    public CVertexShader
{
public:
    COGLVertexShader();
    ~COGLVertexShader();

    void clear()                override;

    unsigned int m_VertexShader;
};