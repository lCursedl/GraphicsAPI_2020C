#pragma once
#include "CGraphicsAPI.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

class CDXGraphicsAPI :
    public CGraphicsAPI
{
public:
    bool init(HWND window)                                    override;

    //DEVICE

    bool createRTV(CRTV* rtv, CTexture* tex = nullptr)        override;
    bool createTexture(CTexture* tex, CRTV* rtv = nullptr)    override;

    CShaderProgram* createShaderProgram(std::wstring vsfile,
        std::wstring psfile)                                  override;

    CBuffer* createBuffer(const void* data,
        unsigned int size,
        BUFFER_TYPE type)                                     override;

    //DEVICE CONTEXT

    void setBackBuffer()                                      override;
    void setViewport(int width, int height)                   override;

    //MISC

    void compileFile();

private:
    D3D_DRIVER_TYPE         m_DriverType;
    D3D_FEATURE_LEVEL       m_FeatureLevel;

    ID3D11Device*           m_Device;
    ID3D11DeviceContext*    m_DeviceContext;
    IDXGISwapChain*         m_SwapChain;
    ID3D11Texture2D*        m_BackBuffer;
    ID3D11RenderTargetView* m_RTV;
    ID3D11Texture2D*        m_DepthStencil;
    ID3D11DepthStencilView* m_DSV;
};    