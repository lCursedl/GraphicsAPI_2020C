#include "COGLBuffer.h"

COGLBuffer::COGLBuffer(){}

COGLBuffer::~COGLBuffer(){}

void COGLBuffer::clear()
{
	glDeleteBuffers(1, &m_Buffer);
}