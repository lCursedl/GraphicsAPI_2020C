#include "CDXVertexShader.h"

CDXVertexShader::CDXVertexShader()
{
	m_Blob = NULL;
	m_VS = NULL;
}

CDXVertexShader::~CDXVertexShader()
{
	if (m_Blob)
	{
		m_Blob->Release();
	}
	if (m_VS)
	{
		m_VS->Release();
	}
}
