#include "CDXSamplerState.h"

CDXSamplerState::CDXSamplerState()
{
	m_Sampler = nullptr;
}

CDXSamplerState::~CDXSamplerState()
{
	if (m_Sampler)
	{
		m_Sampler->Release();
	}
}