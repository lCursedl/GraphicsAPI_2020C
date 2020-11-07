#pragma once
#include "CSamplerState.h"
#include <d3d11.h>
class CDXSamplerState :
    public CSamplerState
{
public:

    CDXSamplerState();
    ~CDXSamplerState();
private:

    ID3D11SamplerState* m_Sampler;

    friend class CDXGraphicsAPI;
};