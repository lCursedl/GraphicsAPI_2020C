#pragma once
#include "CTexture.h"
#include <glad/glad.h>

/** \class COGLTexture
*   \brief Class which holds info for an OpenGL texture.
*/
class COGLTexture :
    public CTexture
{
protected:

    /** \fn COGLTexture()
    *   \brief Class constructor.
    */
    COGLTexture();

public:
    

    /** \fn ~COGLTexture()
    *   \brief Class destructor.
    *   if m_iTexture or m_iFramebuffer was used, release memory before deleting object.
    */
    ~COGLTexture();

private:

    unsigned int m_iTexture;        /**< unsigned int for OpenGL texture index */
    unsigned int m_iFramebuffer;    /**< unsigned int for OpenGL framebuffer index */

    friend class COGLGraphicsAPI;
};