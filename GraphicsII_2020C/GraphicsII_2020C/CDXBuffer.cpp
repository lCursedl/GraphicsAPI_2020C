#include "CDXBuffer.h"

CDXBuffer::CDXBuffer()
{
	m_Buffer = nullptr;
}

CDXBuffer::~CDXBuffer()
{
	if (m_Buffer)
	{
		m_Buffer->Release();
	}
}