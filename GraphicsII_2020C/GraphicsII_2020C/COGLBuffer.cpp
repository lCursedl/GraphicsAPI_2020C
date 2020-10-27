#include "COGLBuffer.h"

COGLBuffer::COGLBuffer(){}

COGLBuffer::~COGLBuffer()
{
	glDeleteBuffers(1, &m_Buffer);
}