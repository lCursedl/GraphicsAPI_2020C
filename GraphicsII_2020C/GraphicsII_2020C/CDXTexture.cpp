#include "CDXTexture.h"

CDXTexture::CDXTexture(){}

void CDXTexture::clear()
{
    if (m_pTexture)
    {
        m_pTexture->Release();
    }
    if (m_pRTV)
    {
        m_pRTV->Release();
    }
    if (m_pDepthTexture)
    {
        m_pDepthTexture->Release();
    }
    if (m_pDSV)
    {
        m_pDSV->Release();
    }
}