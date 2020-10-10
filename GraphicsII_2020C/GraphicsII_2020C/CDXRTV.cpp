#include "CDXRTV.h"

CDXRTV::CDXRTV()
{
	m_pRTV = NULL;
}

CDXRTV::~CDXRTV(){}

void CDXRTV::clear()
{
	if (m_pRTV)
	{
		m_pRTV->Release();
	}
	if (m_DSV)
	{
		m_DSV->Release();
	}
}
