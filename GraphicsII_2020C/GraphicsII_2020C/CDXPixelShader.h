#pragma once
#include "CShader.h"
#include <d3d11.h>

class CDXPixelShader :
    public CPixelShader
{
public:

    CDXPixelShader();
    ~CDXPixelShader();

    void clear()                override;

    ID3D11PixelShader* m_PS;
    ID3DBlob* m_Blob;
};