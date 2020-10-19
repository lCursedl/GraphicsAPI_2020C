#pragma once
#include "CGraphicsAPI.h"
#include <glad/glad.h>
#include <glad/glad_wgl.h>
class COGLGraphicsAPI :
    public CGraphicsAPI
{
public:
    bool init(HWND window);

    //DEVICE

    bool createRTV(CRTV* rtv, CTexture* tex = nullptr)        override;
    bool createTexture(CTexture* tex, CRTV* rtv = nullptr)    override;
    bool compileAndCreateVertexShader(WCHAR* filename,
        CVertexShader* shader,
        LPCSTR entryPoint,
        LPCSTR shaderModel)                                   override;
    bool compileAndCreatePixelShader(WCHAR* filename,
        CPixelShader* shader,
        LPCSTR entryPoint,
        LPCSTR shaderModel)                                   override;
    CBuffer* createBuffer(const void* data,
        unsigned int size,
        BUFFER_TYPE type)                                     override;

    //DEVICE CONTEXT

    void setBackBuffer()                                      override;
    void setViewport(int width, int height)                   override;
    
};