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
protected:

    /** \fn COGLShaderProgram()
    *   \brief Class constructor.
    */
    COGLShaderProgram() = default;

public:    

    /** \fn ~COGLShaderProgram()
    *   \brief Class destructor.
    *   If m_Program was used, release memory before deleting object.
    */
    ~COGLShaderProgram();

    void setVertexShader(CVertexShader* vertexShader)               override;

    void setPixelShader(CPixelShader* pixelShader)                  override;

    void linkProgram()                                              override;

private:
    unsigned int m_Program;         /**< unsigned int for OpenGL shader program index. */

    friend class COGLGraphicsAPI;
};