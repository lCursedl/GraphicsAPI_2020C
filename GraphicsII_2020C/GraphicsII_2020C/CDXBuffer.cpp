#include "CDXBuffer.h"

CDXBuffer::CDXBuffer()
{
	m_Buffer = NULL;
	ZeroMemory(&m_Desc, sizeof(m_Desc));
}

CDXBuffer::~CDXBuffer()
{
	if (m_Buffer)
	{
		m_Buffer->Release();
	}
}