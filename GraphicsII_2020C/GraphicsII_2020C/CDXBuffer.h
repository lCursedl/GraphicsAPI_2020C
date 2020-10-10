#pragma once
#include "CBuffer.h"
#include <d3d11.h>
class CDXBuffer :
    public CBuffer
{
public:

    CDXBuffer();
    ~CDXBuffer();

    void init(unsigned int size, BUFFER_TYPE type)  override;
    void clear()                                    override;

    ID3D11Buffer* m_Buffer;
    D3D11_BUFFER_DESC m_Desc;
};