#pragma once
#include "CShaderProgram.h"
class COGLShaderProgram :
    public CShaderProgram
{
public:
    COGLShaderProgram();
    ~COGLShaderProgram();

    unsigned int m_Program;
};