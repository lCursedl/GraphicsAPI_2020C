#include "COGLInputLayout.h"

COGLInputLayout::~COGLInputLayout()
{
	glDeleteVertexArrays(1, &VAO);
}