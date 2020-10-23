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

    CTexture* createTexture(int width, int height)            override;

    CShaderProgram* createShaderProgram(std::wstring vsfile,
        std::wstring psfile)                                  override;

    CBuffer* createBuffer(const void* data,
        unsigned int size,
        BUFFER_TYPE type)                                     override;

    CInputLayout* createInputLayout(CShaderProgram* program,
        LAYOUT_DESC desc)                                     override;

    //DEVICE CONTEXT

    void setBackBuffer()                                      override;
    void setViewport(int width, int height)                   override;
    void setShaders(CShaderProgram* program)                  override;
    void draw(unsigned int indices)                           override;
    void clearBackBuffer(float red, float green, float blue)  override;
    //MISC

    HRESULT compileShaderFromFile(std::wstring fileName,
        std::string shaderModel,
        ID3DBlob** ppBlobOut);

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