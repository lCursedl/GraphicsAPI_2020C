#include "COGLInputLayout.h"

COGLInputLayout::COGLInputLayout()
{
}

void COGLInputLayout::clear()
{
	glDeleteVertexArrays(1, &VAO);
}
