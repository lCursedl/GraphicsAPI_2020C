#pragma once
#include <d3d11.h>
#include "CTexture.h"
class CDXTexture :
    public CTexture
{
public:
    CDXTexture();
    ~CDXTexture();

    void init(
		unsigned int Width,
		unsigned int Height,
		unsigned int Miplevels,
		unsigned int ArraySize,
		unsigned int Format,
		unsigned int Count,
		unsigned int Quality,
		unsigned int Usage,
		unsigned int Flags,
		unsigned int CPUAccessFlags,
		unsigned int MiscFlags)	override;

	void clear()				override;

	ID3D11Texture2D*	m_pTexture;
	D3D11_TEXTURE2D_DESC m_Desc;
	ID3D11RenderTargetView* m_pRTV;
	ID3D11DepthStencilView* m_pDSV;
};