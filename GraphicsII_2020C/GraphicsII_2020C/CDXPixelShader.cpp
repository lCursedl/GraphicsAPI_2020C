#include "CDXPixelShader.h"

CDXPixelShader::CDXPixelShader()
{
	m_PS = NULL;
	m_Blob = NULL;
}

CDXPixelShader::~CDXPixelShader(){}

void CDXPixelShader::clear()
{
	if (m_PS)
	{
		m_PS->Release();
	}
	if (m_Blob)
	{
		m_Blob->Release();
	}
}
