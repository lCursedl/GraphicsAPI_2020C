#include "COGLBuffer.h"

COGLBuffer::~COGLBuffer()
{
	glDeleteBuffers(1, &m_Buffer);
}