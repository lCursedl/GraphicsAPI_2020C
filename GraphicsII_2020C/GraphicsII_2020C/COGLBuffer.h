#pragma once
#include "CBuffer.h"
#include <glad/glad.h>

class COGLBuffer :
    public CBuffer
{
public:

    COGLBuffer();
    ~COGLBuffer();

private:

    GLenum m_Type;
    unsigned int m_Size;
    unsigned int m_Buffer;

    friend class COGLGraphicsAPI;
};