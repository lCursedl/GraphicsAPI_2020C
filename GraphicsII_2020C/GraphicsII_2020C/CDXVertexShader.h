#pragma once
#include "CShader.h"
#include <d3d11.h>
class CDXVertexShader :
    public CVertexShader
{
public:

    CDXVertexShader();
    ~CDXVertexShader();

    void clear()            override;

    ID3DBlob* m_Blob;
    ID3D11VertexShader* m_VS;
    ID3D11InputLayout* m_InputLayout;
};