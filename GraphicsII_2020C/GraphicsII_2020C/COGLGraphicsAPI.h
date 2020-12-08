#pragma once
#include "CGraphicsAPI.h"
#include <glad/glad.h>
//#include <glad/glad_wgl.h>
class COGLGraphicsAPI :
    public CGraphicsAPI
{
private:

    void readShaderFile(std::wstring file, std::string& source);
    std::map<FORMATS, std::pair<int, int>>m_Formats;
    HDC m_Handle;
    HGLRC oglRenderContext;
    void fillFormats();
    GLenum m_Topology;

public:
    bool init(HWND window);
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
        unsigned int stride,
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
    void setViewport(int topLeftX,
        int topLeftY,
        int width,
        int height)                                           override;
    void setShaders(CShaderProgram* program)                  override;
    void drawIndexed(unsigned int indices)                    override;
    void draw(unsigned int count, unsigned int first)         override;
    void clearBackBuffer(COLOR color)                         override;
    void setInputLayout(CInputLayout* layout)                 override;
    void setRenderTarget(CTexture* texture, CTexture* depth)  override;
    void updateBuffer(CBuffer* buffer, const void* data)      override;
    void setVertexBuffer(CBuffer* buffer)  override;
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
};