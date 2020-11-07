#pragma once
#include "CSamplerState.h"
class COGLSamplerState :
    public CSamplerState
{
public:
    COGLSamplerState();
    ~COGLSamplerState();

private:
    unsigned int m_Sampler;

    friend class COGLGraphicsAPI;
};