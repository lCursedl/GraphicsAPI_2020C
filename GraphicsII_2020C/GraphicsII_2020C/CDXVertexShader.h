#pragma once
#include "CShader.h"
#include <d3d11.h>

/** \class CDXVertexShader
*   \brief Class which holds info for a D3D11's vertex shader.
*/
class CDXVertexShader :
    public CVertexShader
{
public:
    /** \fn CDXVertexShader()
    *   \brief Class constructor.
    * 
    *   Sets m_Blob & m_VS as nullptr.
    */
    CDXVertexShader();

    /** \fn ~CDXVertexShader()
    *   \brief Class destructor.
    * 
    *   If m_Blob or m_VS was used, release memory before deleting object.
    */
    ~CDXVertexShader();

private:

    ID3DBlob* m_Blob;               /**< ID3D11Blob pointer */
    ID3D11VertexShader* m_VS;       /**< ID3D11VertexShader pointer */

    friend class CDXGraphicsAPI;
};