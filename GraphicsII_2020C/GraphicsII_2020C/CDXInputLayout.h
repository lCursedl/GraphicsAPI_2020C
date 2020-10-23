#pragma once
#include "CInputLayout.h"
#include <d3d11.h>

class CDXInputLayout :
    public CInputLayout
{
public:
    CDXInputLayout();

    void clear()                        override;

    ID3D11InputLayout* m_InputLayout = nullptr;
};