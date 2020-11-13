#pragma once
#include <d3d11.h>
#include "CTexture.h"

/**	\class CDXTexture
*	\brief Class which holds info for a D3D11's texture.
*/
class CDXTexture :
    public CTexture
{
public:
	/**	\fn CDXTexture()
	*	\brief Class constructor.
	* 
	*	Sets m_pTexture, m_pRTV, m_pDSV and m_pSRV as nullptr;
	*/
    CDXTexture();

	/** \fn ~CDXTexture()
	*	\brief Class destructor.
	*	
	*	If m_pTexture, m_pRTV, m_pDSV or m_pSRV was used, release memory before
	*	deleting object.
	*/
	~CDXTexture();

private:

	ID3D11Texture2D*			m_pTexture;	/**< ID3D11Texture2D pointer */
	ID3D11RenderTargetView*		m_pRTV;		/**< ID3D11RenderTargetView pointer */
	ID3D11DepthStencilView*		m_pDSV;		/**< ID3D11DepthStencilView pointer */
	ID3D11ShaderResourceView*	m_pSRV;		/**< ID3D11ShaderResourceView pointer */

	friend class CDXGraphicsAPI;
};