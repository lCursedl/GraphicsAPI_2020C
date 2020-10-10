#include "COGLBuffer.h"

COGLBuffer::COGLBuffer(){}

COGLBuffer::~COGLBuffer(){}

void COGLBuffer::init(unsigned int size, BUFFER_TYPE type)
{
	glGenBuffers(1, &m_Buffer);
	m_Size = size;
	switch (type)
	{
	case VERTEX_BUFFER:
		m_Type = GL_ARRAY_BUFFER;
		break;
	case INDEX_BUFFER:
		m_Type = GL_ELEMENT_ARRAY_BUFFER;
		break;
	case CONST_BUFFER:
		m_Type = GL_UNIFORM_BLOCK;
		break;
	}
}

void COGLBuffer::clear()
{
	glDeleteBuffers(1, &m_Buffer);
}
