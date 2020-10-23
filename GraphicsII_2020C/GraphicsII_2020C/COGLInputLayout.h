#pragma once
#include "CInputLayout.h"
#include <glad/glad.h>
class COGLInputLayout :
    public CInputLayout
{
public:
    COGLInputLayout();

    void clear()                      override;

    unsigned int VAO;
};
