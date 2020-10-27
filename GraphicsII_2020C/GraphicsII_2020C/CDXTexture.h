#pragma once
#include <d3d11.h>
#include "CTexture.h"
class CDXTexture :
    public CTexture
{
public:
    CDXTexture();
	~CDXTexture();

private:

	ID3D11Texture2D*			m_pTexture	= nullptr;
	ID3D11RenderTargetView*		m_pRTV		= nullptr;
	ID3D11DepthStencilView*		m_pDSV		= nullptr;
	ID3D11ShaderResourceView*	m_pSRV		= nullptr;

	friend class CDXGraphicsAPI;
};