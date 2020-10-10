#pragma once
#include <d3d11.h>
#include "CRTV.h"
class CDXRTV :
    public CRTV
{
public:
    CDXRTV();
    ~CDXRTV();

    void clear()                override;

    ID3D11RenderTargetView* m_pRTV;
    ID3D11DepthStencilView* m_DSV;
};