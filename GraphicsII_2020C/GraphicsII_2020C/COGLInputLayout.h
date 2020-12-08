#pragma once
#include "CInputLayout.h"
#include <glad/glad.h>

/** \class CDXInputLayout
*   \brief Class which holds info for a D3D11's input layout.
*/
class COGLInputLayout :
    public CInputLayout
{
protected:

    /** \fn COGLInputLayout()
        *   \brief Class constructor.
        */
    COGLInputLayout() = default;

public:    
    
    /** \fn ~COGLInputLayout()
    *   \brief Class destructor.
    *
    *   If VAO was used, release memory before deleting object.
    */
    ~COGLInputLayout();

private:
    unsigned int VAO;   /**< unsigned int for OpenGL VAO index */

    friend class COGLGraphicsAPI;
};