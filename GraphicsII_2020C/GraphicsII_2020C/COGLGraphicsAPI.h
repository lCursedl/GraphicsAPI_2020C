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

public:
    bool init(HWND window);
    void shutdown()                                           override;

    //DEVICE

    CTexture* createTexture(int width,
        int height,
        TEXTURE_BINDINGS binding,
        FORMATS format)                               override;
    CShaderProgram* createShaderProgram(std::wstring vsfile,
        std::wstring psfile)                                  override;
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
    //DEVICE CONTEXT

    void setBackBuffer()                                      override;
    void setViewport(int width, int height)                   override;
    void setShaders(CShaderProgram* program)                  override;
    void drawIndexed(unsigned int indices)                    override;
    void clearBackBuffer(float red, float green, float blue)  override;
    void setInputLayout(CInputLayout* layout)                 override;
    void setRenderTarget(CTexture* texture, CTexture* depth)  override;
    void updateBuffer(CBuffer* buffer, const void* data)      override;
    void setVertexBuffer(CBuffer* buffer, unsigned int size)  override;
    void setIndexBuffer(CBuffer* buffer)                      override;
    void setSamplerState(CTexture* texture,
        CSamplerState* sampler)                               override;
    void setConstantBuffer(unsigned int slot,
        CBuffer* buffer,
        SHADER_TYPE shaderType)                               override;

    //SWAPCHAIN
    void swapBuffer()                                         override;
};