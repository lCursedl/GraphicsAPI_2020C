#include "CDXBuffer.h"

CDXBuffer::CDXBuffer()
{
	m_Buffer = NULL;
	ZeroMemory(&m_Desc, sizeof(m_Desc));
}

CDXBuffer::~CDXBuffer()
{
	clear();
}

void CDXBuffer::init(unsigned int size, BUFFER_TYPE type)
{
	m_Desc.Usage = D3D11_USAGE_DEFAULT;
	m_Desc.ByteWidth = (UINT)size;
	m_Desc.CPUAccessFlags = 0;
	switch (type)
	{
	case VERTEX_BUFFER:
		m_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		break;
	case INDEX_BUFFER:
		m_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		break;
	case CONST_BUFFER:
		m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		break;
	}
}

void CDXBuffer::clear()
{
	if (m_Buffer)
	{
		m_Buffer->Release();
	}
}
