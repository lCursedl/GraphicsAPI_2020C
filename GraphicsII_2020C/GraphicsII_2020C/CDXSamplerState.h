#pragma once
#include "CSamplerState.h"
#include <d3d11.h>

/** \class CDXSamplerState
*   \brief Class which holds info for a D3D11's sampler state.
*/
class CDXSamplerState :
    public CSamplerState
{
protected:

    /** \fn CDXSamplerState()
    *   \brief Class constructor
    * 
    *   Sets m_Sampler as nullptr;
    */
    CDXSamplerState();

public:
    
    /** \fn ~CDXSamplerState()
    *   \brief Class destructor
    * 
    *   If m_Sampler was used, release memory before deleting object.
    */
    ~CDXSamplerState();

private:

    ID3D11SamplerState* m_Sampler;      /**< ID3D11SamplerState pointer. */

    friend class CDXGraphicsAPI;
};