#pragma once
#include "CShaderProgram.h"
#include <glad/glad.h>

/** \class COGLShaderProgram
*   \brief Class which holds info for an OpenGL shader program.
*   The concept of ShaderProgram exists only on OGl, therefore the functionality of
*   the base class is expanded here.
*/
class COGLShaderProgram :
    public CShaderProgram
{
public:
    /** \fn COGLShaderProgram()
    *   \brief Class constructor.
    *   Initializes m_pVertexShader as an COGLVertexShader 
    *   & m_pPixelShader as COGLPixelShader
    */
    COGLShaderProgram();

    /** \fn ~COGLShaderProgram()
    *   \brief Class destructor.
    *   If m_pVertexShader or m_pPixelSHader were used, release memory before deleting
    *   object.
    */
    ~COGLShaderProgram();

private:
    unsigned int m_Program;         /**< unsigned int for OpenGL shader program index. */

    friend class COGLGraphicsAPI;
};