#pragma once
#include "CShader.h"
#include <d3d11.h>

/** \class CDXPixelShader
*   \brief Class which holds info for a D3D11's pixel shader.
*/
class CDXPixelShader :
    public CPixelShader
{
public:    

    /** \fn ~CDXPixelShader()
    *   \brief Class destructor.
    * 
    *   If m_PS or m_Blob was used, release memory before deleting object.
    */
    ~CDXPixelShader();

protected:

    /** \fn CDXPixelShader()
    *   \brief Class constructor.
    *
    *   Sets m_PS & m_Blob as nullptr.
    */
    CDXPixelShader();

private:
    ID3D11PixelShader* m_PS;        /**< ID3D11PixelShader pointer */
    ID3DBlob* m_Blob;               /**< ID3D11Blob pointer */

    friend class CDXGraphicsAPI;
};