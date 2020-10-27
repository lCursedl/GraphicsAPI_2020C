#include "CDXInputLayout.h"

CDXInputLayout::CDXInputLayout(){}

CDXInputLayout::~CDXInputLayout()
{
	if (m_InputLayout)
	{
		m_InputLayout->Release();
	}
}