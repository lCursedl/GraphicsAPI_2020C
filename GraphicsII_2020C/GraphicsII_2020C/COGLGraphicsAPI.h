#pragma once
#include "CGraphicsAPI.h"
#include <glad/glad.h>
//#include <glad/glad_wgl.h>
class COGLGraphicsAPI :
    public CGraphicsAPI
{
private:

    const char* readShaderFile(std::wstring file);
    std::map<TEXTURE_FORMATS, std::pair<int, int>>m_Formats;

public:
    bool init(HWND window);

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
};