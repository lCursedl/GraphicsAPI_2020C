#pragma once
#include "CGraphicsAPI.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <algorithm>

class CDXGraphicsAPI :
    public CGraphicsAPI
{
public:
    bool init(HWND window)                                    override;
    void shutdown()                                           override;

    //DEVICE

    CTexture* createTexture(int width,
        int height,
        TEXTURE_BINDINGS binding,
        FORMATS format)                                       override;

    CTexture* createTextureFromFile(std::string path)         override;

    CShaderProgram* createShaderProgram()                     override;

    CBuffer* createBuffer(const void* data,
        unsigned int size,
        BUFFER_TYPE type)                                     override;

    CInputLayout* createInputLayout(CShaderProgram* program,
        LAYOUT_DESC desc)                                     override;
    CSamplerState* createSamplerState(FILTER_LEVEL mag,
        FILTER_LEVEL min,
        FILTER_LEVEL mip,
        unsigned int anisotropic,
        WRAPPING wrapMode)                                    override;
    CVertexShader* createVertexShader(std::wstring file)      override;
    CPixelShader* createPixelShader(std::wstring file)        override;

    //DEVICE CONTEXT

    void setBackBuffer()                                      override;
    void setViewport(int width, int height)                   override;
    void setShaders(CShaderProgram* program)                  override;
    void drawIndexed(unsigned int indices)                    override;
    void draw(unsigned int count, unsigned int first)         override;
    void clearBackBuffer(COLOR color)                         override;
    void setInputLayout(CInputLayout* layout)                 override;
    void setRenderTarget(CTexture* texture, CTexture* depth)  override;
    void updateBuffer(CBuffer* buffer, const void* data)      override;
    void setVertexBuffer(CBuffer* buffer, unsigned int size)  override;
    void setIndexBuffer(CBuffer* buffer)                      override;
    void setSamplerState(unsigned int slot,
        CTexture* texture,
        CSamplerState* sampler)                               override;
    void setConstantBuffer(unsigned int slot,
        CBuffer* buffer,
        SHADER_TYPE shaderType)                               override;
    void clearRenderTarget(CTexture* rt, COLOR color)         override;
    void clearDepthStencil(CTexture* ds)                      override;
    void setTexture(unsigned int slot, CTexture* texture)     override;
    void setTopology(TOPOLOGY topology)                       override;

    //SWAPCHAIN

    void swapBuffer()                                         override;

private:
    ID3D11Device*           m_Device;
    ID3D11DeviceContext*    m_DeviceContext;
    IDXGISwapChain*         m_SwapChain;
    CTexture*               m_BackBuffer;
    CTexture*               m_DepthStencil;

    std::map<FORMATS, DXGI_FORMAT> m_Formats;

    HRESULT compileShaderFromFile(std::wstring fileName,
        std::string shaderModel,
        ID3DBlob** ppBlobOut);
    void fillFormats();
};    