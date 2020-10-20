#pragma once
#include <d3d11.h>
#include "CTexture.h"
class CDXTexture :
    public CTexture
{
public:
    CDXTexture();
	void clear()				override;

	ID3D11Texture2D*		m_pTexture		= nullptr;
	ID3D11Texture2D*		m_pDepthTexture = nullptr;
	ID3D11RenderTargetView* m_pRTV			= nullptr;
	ID3D11DepthStencilView* m_pDSV			= nullptr;
};