#include "CDXInputLayout.h"

CDXInputLayout::CDXInputLayout(){}

void CDXInputLayout::clear()
{
	if (m_InputLayout)
	{
		m_InputLayout->Release();
	}
}