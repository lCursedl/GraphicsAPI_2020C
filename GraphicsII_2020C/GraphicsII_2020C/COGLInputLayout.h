#pragma once
#include "CInputLayout.h"
#include <glad/glad.h>
class COGLInputLayout :
    public CInputLayout
{
public:
    COGLInputLayout();
    ~COGLInputLayout();

private:
    unsigned int VAO;

    friend class COGLGraphicsAPI;
};
