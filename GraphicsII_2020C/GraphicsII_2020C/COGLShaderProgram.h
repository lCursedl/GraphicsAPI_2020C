#pragma once
#include "CShaderProgram.h"
#include <glad/glad.h>
class COGLShaderProgram :
    public CShaderProgram
{
public:
    COGLShaderProgram();
    ~COGLShaderProgram();

private:
    unsigned int m_Program;

    friend class COGLGraphicsAPI;
};