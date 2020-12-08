#pragma once
#include "CSamplerState.h"

/** \class COGLSamplerState
*   \brief Class which holds info for an OpenGL sampler object.
*/
class COGLSamplerState :
    public CSamplerState
{
protected:

    /** \fn COGLSamplerState()
    *   \brief Class constructor.
    *   
    *   Sets m_Sampler as 0.
    */
    COGLSamplerState();

public:
    
    /** \fn ~COGLSamplerState
    *   \brief Class destructor.
    * 
    *   If m_Sampler was used, release memory before deleting object.
    */
    ~COGLSamplerState();

private:
    unsigned int m_Sampler;         /**< unsigned int for an OpenGL sampler object */

    friend class COGLGraphicsAPI;
};