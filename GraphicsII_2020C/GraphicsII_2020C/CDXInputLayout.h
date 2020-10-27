#pragma once
#include "CInputLayout.h"
#include <d3d11.h>

class CDXInputLayout :
    public CInputLayout
{
public:
    CDXInputLayout();
    ~CDXInputLayout();

private:

    ID3D11InputLayout* m_InputLayout = nullptr;

    friend class CDXGraphicsAPI;
};