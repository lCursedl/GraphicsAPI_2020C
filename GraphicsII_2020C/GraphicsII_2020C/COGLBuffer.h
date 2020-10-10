#pragma once
#include "CBuffer.h"
#include <glad/glad.h>

class COGLBuffer :
    public CBuffer
{
public:

    COGLBuffer();
    ~COGLBuffer();

    void init(unsigned int size, BUFFER_TYPE type)  override;
    void clear()                                    override;

    GLenum m_Type;
    unsigned int m_Size;
    unsigned int m_Buffer;
};