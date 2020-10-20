#include "COGLGraphicsAPI.h"
#include "COGLRTV.h"
#include "COGLTexture.h"
#include "COGLVertexShader.h"
#include "COGLPixelShader.h"
#include "COGLBuffer.h"
#include "COGLShaderProgram.h"
#include <string>
#include <fstream>
#include <sstream>

const char* COGLGraphicsAPI::readShaderFile(std::wstring file)
{
	std::string code;
	std::ifstream shaderFile;
	const char* shaderCode;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		shaderFile.open(file);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		code = shaderStream.str();
		shaderCode = code.c_str();
	}
	catch (std::ifstream::failure e)
	{
		return nullptr;
	}
	
	return shaderCode;
}

bool COGLGraphicsAPI::init(HWND window)
{
	if (!gladLoadGL())
	{
		return false;
	}
	RECT rc;
	GetWindowRect(window, &rc);
	setViewport(rc.right - rc.left, rc.bottom - rc.top);
	return true;
}

CTexture* COGLGraphicsAPI::createTexture(int width, int height)
{
	COGLTexture* Tex = new COGLTexture();
	//Create texture
	glBindTexture(GL_TEXTURE_2D, Tex->m_iTexture);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB,
		width,
		height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Create RenderBufferObject for depth and stencil
	glGenRenderbuffers(1, &Tex->m_iRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, Tex->m_iRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	return Tex;
}

CShaderProgram* COGLGraphicsAPI::createShaderProgram(std::wstring vsfile,
	std::wstring psfile)
{
	const char* source;
	int result;
	char log[512];
	source = readShaderFile(vsfile);
	COGLVertexShader* VS = new COGLVertexShader();
	VS->m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VS->m_VertexShader, 1, &source, NULL);
	glCompileShader(VS->m_VertexShader);

	glGetShaderiv(VS->m_VertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(VS->m_VertexShader, 512, NULL, log);
		OutputDebugStringA(log);
		VS->clear();
		delete VS;
		return nullptr;
	}

	source = readShaderFile(psfile);
	COGLPixelShader* PS = new COGLPixelShader();
	PS->m_PS = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(PS->m_PS, 1, &source, NULL);
	glCompileShader(PS->m_PS);

	glGetShaderiv(PS->m_PS, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(PS->m_PS, 512, NULL, log);
		OutputDebugStringA(log);
		VS->clear();
		delete VS;
		PS->clear();
		delete PS;
		return nullptr;
	}

	COGLShaderProgram* ShaderProgram = new COGLShaderProgram();
	ShaderProgram->setVertexShader(VS);
	ShaderProgram->setPixelShader(PS);

	ShaderProgram->m_Program = glCreateProgram();
	glAttachShader(ShaderProgram->m_Program, VS->m_VertexShader);
	glAttachShader(ShaderProgram->m_Program, PS->m_PS);
	glLinkProgram(ShaderProgram->m_Program);

	glGetProgramiv(ShaderProgram->m_Program, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(ShaderProgram->m_Program, 512, NULL, log);
		OutputDebugStringA(log);
		ShaderProgram->clear();
		delete ShaderProgram;
		delete VS;
		delete PS;
		return nullptr;
	}

	return ShaderProgram;
}

void COGLGraphicsAPI::setBackBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void COGLGraphicsAPI::setViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void COGLGraphicsAPI::setShaders(CShaderProgram* program)
{
	COGLShaderProgram* ShaderProgram = dynamic_cast<COGLShaderProgram*>(program);
	glUseProgram(ShaderProgram->m_Program);
}

void COGLGraphicsAPI::draw(unsigned int indices)
{
	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
}

void COGLGraphicsAPI::clearBackBuffer(float red, float green, float blue)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

CBuffer* COGLGraphicsAPI::createBuffer(const void* data,
	unsigned int size,
	BUFFER_TYPE type)
{
	COGLBuffer* OGLBuffer = new COGLBuffer();

	glGenBuffers(1, &OGLBuffer->m_Buffer);
	OGLBuffer->m_Size = size;

	switch (type)
	{
	case VERTEX_BUFFER:
		OGLBuffer->m_Type = GL_ARRAY_BUFFER;
		break;
	case INDEX_BUFFER:
		OGLBuffer->m_Type = GL_ELEMENT_ARRAY_BUFFER;
		break;
	case CONST_BUFFER:
		OGLBuffer->m_Type = GL_UNIFORM_BLOCK;
		break;
	}

	glBindBuffer(OGLBuffer->m_Type, OGLBuffer->m_Buffer);
	glBufferData(OGLBuffer->m_Type, OGLBuffer->m_Size, data, GL_STATIC_DRAW);
}
