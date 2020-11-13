#include "CDXInputLayout.h"

CDXInputLayout::CDXInputLayout()
{
	m_InputLayout = nullptr;
}

CDXInputLayout::~CDXInputLayout()
{
	if (m_InputLayout)
	{
		m_InputLayout->Release();
	}
}