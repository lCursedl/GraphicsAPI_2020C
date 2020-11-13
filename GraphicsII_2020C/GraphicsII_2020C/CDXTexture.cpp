#include "CDXTexture.h"

CDXTexture::CDXTexture()
{
    m_pTexture = nullptr;
    m_pRTV = nullptr;
    m_pDSV = nullptr;
    m_pSRV = nullptr;
}

CDXTexture::~CDXTexture()
{
    if (m_pTexture)
    {
        m_pTexture->Release();
    }
    if (m_pRTV)
    {
        m_pRTV->Release();
    }
    if (m_pDSV)
    {
        m_pDSV->Release();
    }
    if (m_pSRV)
    {
        m_pSRV->Release();
    }
}