#pragma once
#include "CShader.h"
#include <glad/glad.h>

/** \class COGLVertexShader
*   \brief Class which holds info for a OpenGL vertex shader
*/
class COGLVertexShader :
    public CVertexShader
{
public:
    /** \fn COGLVertexShader()
    *   \brief Class constructor.
    */
    COGLVertexShader();

    /** ~COGLVertexShader()
    *   \brief Class destructor.
    *   If m_VertexShader was used, release memory before deleting object.
    */
    ~COGLVertexShader();

private:
    unsigned int m_VertexShader;    /**< unsigned int for OpenGL vertex shader index. */

    friend class COGLGraphicsAPI;
};