#pragma once
#include "CBuffer.h"
#include <glad/glad.h>

/** \class COGLBuffer
*   \brief Class which holds info for an OpenGL buffer.
*/
class COGLBuffer :
    public CBuffer
{
protected:

    /** \fn COGLBuffer()
    *   \brief Class constructor.
    */
    COGLBuffer() = default;
    

public:    

    ~COGLBuffer();
    /** \fn ~COGLBuffer()
    *   \brief Class destructor.
    *   If m_Buffer was used, release memory before deleting object.
    */

private:

    unsigned int m_Type;    /**< unsigned int for buffer type storing. */
    int m_Size;             /**< int for buffer size storing. */
    int m_Stride;           /**< int for buffer stride storing.*/
    unsigned int m_Buffer;  /**< unsigned int for OpenGL buffer index */

    friend class COGLGraphicsAPI;
};