#pragma once
#include "CGraphicsAPI.h"
#include <glad/glad.h>
#include <glad/glad_wgl.h>
class COGLGraphicsAPI :
    public CGraphicsAPI
{
private:

    const char* readShaderFile(std::wstring file);

public:
    bool init(HWND window);


    //DEVICE

    CTexture* createTexture(int width, int height)    override;
    CShaderProgram* createShaderProgram(std::wstring vsfile,
        std::wstring psfile)                                  override;
    CBuffer* createBuffer(const void* data,
        unsigned int size,
        BUFFER_TYPE type)                                     override;
    
    //DEVICE CONTEXT

    void setBackBuffer()                                      override;
    void setViewport(int width, int height)                   override;
    void setShaders(CShaderProgram* program)                  override;
    void draw(unsigned int indices)                           override;
    void clearBackBuffer(float red, float green, float blue)  override;
};