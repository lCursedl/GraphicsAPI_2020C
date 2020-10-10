#include "CDXTexture.h"

CDXTexture::CDXTexture()
{
    m_pTexture = NULL;
}

CDXTexture::~CDXTexture()
{
}

void CDXTexture::init(
    unsigned int Width,
    unsigned int Height,
    unsigned int Miplevels,
    unsigned int ArraySize,
    unsigned int Format,
    unsigned int Count,
    unsigned int Quality,
    unsigned int Usage,
    unsigned int Flags,
    unsigned int CPUAccessFlags,
    unsigned int MiscFlags)
{
    
    ZeroMemory(&m_Desc, sizeof(m_Desc));

    m_Desc.Width = Width;
    m_Desc.Height = Height;
    m_Desc.MipLevels = Miplevels;
    m_Desc.ArraySize = ArraySize;
    m_Desc.Format = (DXGI_FORMAT)Format;
    m_Desc.SampleDesc.Count = Count;
    m_Desc.SampleDesc.Quality = Quality;
    m_Desc.Usage = (D3D11_USAGE)Usage;
    m_Desc.BindFlags = Flags;
    m_Desc.CPUAccessFlags = CPUAccessFlags;
    m_Desc.MiscFlags = MiscFlags;
}

void CDXTexture::clear()
{
    if (m_pTexture)
    {
        m_pTexture->Release();
    }
}