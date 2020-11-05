#pragma once
#include "CGraphicsAPI.h"
#include <d3d11.h>
#include <d3dcompiler.h>

class CDXGraphicsAPI :
    public CGraphicsAPI
{
public:
    bool init(HWND window)                                    override;

    //DEVICE

    CTexture* createTexture(int width,
        int height,
        TEXTURE_BINDINGS binding,
        TEXTURE_FORMATS format)                               override;

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
    void drawIndexed(unsigned int indices)                    override;
    void clearBackBuffer(float red, float green, float blue)  override;
    void setInputLayout(CInputLayout* layout)                 override;
    void setRenderTarget(CTexture* texture, CTexture* depth)  override;
    void updateBuffer(CBuffer* buffer, const void* data)      override;

private:
    ID3D11Device*           m_Device;
    ID3D11DeviceContext*    m_DeviceContext;
    IDXGISwapChain*         m_SwapChain;
    CTexture*               m_BackBuffer;
    CTexture*               m_DepthStencil;

    std::map<TEXTURE_FORMATS, DXGI_FORMAT> m_Formats;

    HRESULT compileShaderFromFile(std::wstring fileName,
        std::string shaderModel,
        ID3DBlob** ppBlobOut);
};    