#include "CDXVertexShader.h"

CDXVertexShader::CDXVertexShader()
{
	m_Blob = NULL;
	m_VS = NULL;
	m_InputLayout = NULL;
}

CDXVertexShader::~CDXVertexShader(){}

void CDXVertexShader::clear()
{
	if (m_Blob)
	{
		m_Blob->Release();
	}
	if (m_VS)
	{
		m_VS->Release();
	}
	if (m_InputLayout)
	{
		m_InputLayout->Release();
	}
}
