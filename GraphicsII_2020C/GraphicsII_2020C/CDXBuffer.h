#pragma once
#include "CBuffer.h"
#include <d3d11.h>
class CDXBuffer :
    public CBuffer
{
public:

    CDXBuffer();
    ~CDXBuffer();

private:

    ID3D11Buffer* m_Buffer;

    friend class CDXGraphicsAPI;
};