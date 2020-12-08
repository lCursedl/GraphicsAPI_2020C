#pragma once
#include "CShader.h"
#include <glad/glad.h>

/** \class COGLVertexShader
*   \brief Class which holds info for a OpenGL vertex shader
*/
class COGLVertexShader :
    public CVertexShader
{
protected:

    /** \fn COGLVertexShader()
    *   \brief Class constructor.
    */
    COGLVertexShader();

public:
    

    /** ~COGLVertexShader()
    *   \brief Class destructor.
    *   If m_VertexShader was used, release memory before deleting object.
    */
    ~COGLVertexShader() = default;

private:
    unsigned int m_VertexShader;    /**< unsigned int for OpenGL vertex shader index. */

    friend class COGLGraphicsAPI;
    friend class COGLShaderProgram;
};