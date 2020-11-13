#pragma once
#include "CShader.h"
#include <glad/glad.h>

/** \class COGLPixelShader
*   \brief Class which holds info for a OpenGL pixel shader.
*/
class COGLPixelShader :
    public CPixelShader
{
public:
    /** \fn COGLPixelShader()
    *   \brief Class constructor.
    */
    COGLPixelShader();

    /** \fn ~COGLPixelShader()
    *   \brief Class destructor.
    * 
    *   If m_PS was used, release memory before deleting object.
    */
    ~COGLPixelShader();

private:
    unsigned int m_PS;          /**< unsigned int for OpenGL pixel shader index */

    friend class COGLGraphicsAPI;
};