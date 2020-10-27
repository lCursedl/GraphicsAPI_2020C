#include "COGLInputLayout.h"

COGLInputLayout::COGLInputLayout(){}

COGLInputLayout::~COGLInputLayout()
{
	glDeleteVertexArrays(1, &VAO);
}