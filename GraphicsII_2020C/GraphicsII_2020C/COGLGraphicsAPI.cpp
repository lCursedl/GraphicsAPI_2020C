#include "COGLGraphicsAPI.h"
#include "COGLRTV.h"
#include "COGLTexture.h"
#include "COGLVertexShader.h"
#include "COGLPixelShader.h"
#include "COGLBuffer.h"
#include "COGLShaderProgram.h"
#include "COGLInputLayout.h"
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
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC wndHandle = GetDC(window);
	int pixelFormat = ChoosePixelFormat(wndHandle, &pfd);

	SetPixelFormat(wndHandle, pixelFormat, &pfd);

	HGLRC oglRenderContext = wglCreateContext(wndHandle);
	wglMakeCurrent(wndHandle, oglRenderContext);

	if (!gladLoadGL())
	{
		return false;
	}
	RECT rc;
	GetWindowRect(window, &rc);
	setViewport(rc.right - rc.left, rc.bottom - rc.top);

	m_Formats.insert(std::make_pair(R8_SNORM,
					std::make_pair(GL_R8_SNORM, GL_RED)));
	m_Formats.insert(std::make_pair(R16_SNORM,
					std::make_pair(GL_R16_SNORM, GL_RED)));
	m_Formats.insert(std::make_pair(RG8_SNORM,
					std::make_pair(GL_RG8_SNORM, GL_RG)));
	m_Formats.insert(std::make_pair(RG16_SNORM,
					std::make_pair(GL_RG16_SNORM, GL_RG)));
	m_Formats.insert(std::make_pair(RGB10_A2UI,
					std::make_pair(GL_RGB10_A2UI, GL_RGBA)));
	m_Formats.insert(std::make_pair(R16_FLOAT,
					std::make_pair(GL_R16F, GL_RED)));
	m_Formats.insert(std::make_pair(RG16_FLOAT,
					std::make_pair(GL_RG16F, GL_RG)));
	m_Formats.insert(std::make_pair(RGBA16_FLOAT,
					std::make_pair(GL_RGBA16F, GL_RGBA)));
	m_Formats.insert(std::make_pair(R32_FLOAT,
					std::make_pair(GL_R32F, GL_RED)));
	m_Formats.insert(std::make_pair(RG32_FLOAT,		
					std::make_pair(GL_RG32F, GL_RG)));
	m_Formats.insert(std::make_pair(RGB32_FLOAT,	
					std::make_pair(GL_RGB32F, GL_RGB)));
	m_Formats.insert(std::make_pair(RGBA32_FLOAT,	
					std::make_pair(GL_RGBA32F, GL_RGBA)));
	m_Formats.insert(std::make_pair(RG11B10_FLOAT,	
					std::make_pair(GL_R11F_G11F_B10F, GL_RGB)));
	m_Formats.insert(std::make_pair(RGB9_E5,		
					std::make_pair(GL_RGB9_E5, GL_RGB)));
	m_Formats.insert(std::make_pair(R8_INT,			
					std::make_pair(GL_R8I, GL_RED_INTEGER)));
	m_Formats.insert(std::make_pair(R8_UINT,		
					std::make_pair(GL_R8UI, GL_RED_INTEGER)));
	m_Formats.insert(std::make_pair(R16_INT,		
					std::make_pair(GL_R16I, GL_RED_INTEGER)));
	m_Formats.insert(std::make_pair(R16_UINT,		
					std::make_pair(GL_R16UI, GL_RED_INTEGER)));
	m_Formats.insert(std::make_pair(R32_INT,		
					std::make_pair(GL_R32I, GL_RED_INTEGER)));
	m_Formats.insert(std::make_pair(R32_UINT,		
					std::make_pair(GL_R32UI, GL_RED_INTEGER)));
	m_Formats.insert(std::make_pair(RG8_INT,		
					std::make_pair(GL_RG8I, GL_RG_INTEGER)));
	m_Formats.insert(std::make_pair(RG8_UINT,		
					std::make_pair(GL_RG8UI, GL_RG_INTEGER)));
	m_Formats.insert(std::make_pair(RG16_INT,		
					std::make_pair(GL_RG16I, GL_RG_INTEGER)));
	m_Formats.insert(std::make_pair(RG16_UINT,		
					std::make_pair(GL_RG16UI, GL_RG_INTEGER)));
	m_Formats.insert(std::make_pair(RG32_INT,		
					std::make_pair(GL_RG32I, GL_RG_INTEGER)));
	m_Formats.insert(std::make_pair(RG32_UINT,		
					std::make_pair(GL_RG32UI, GL_RG_INTEGER)));
	m_Formats.insert(std::make_pair(RGB32_INT,		
					std::make_pair(GL_RGB32I, GL_RGB_INTEGER)));
	m_Formats.insert(std::make_pair(RGB32_UINT,		
					std::make_pair(GL_RGB32UI, GL_RGB_INTEGER)));
	m_Formats.insert(std::make_pair(RGBA8_INT,		
					std::make_pair(GL_RGBA8I, GL_RGBA_INTEGER)));
	m_Formats.insert(std::make_pair(RGBA8_UINT,		
					std::make_pair(GL_RGBA8UI, GL_RGBA_INTEGER)));
	m_Formats.insert(std::make_pair(RGBA16_INT,		
					std::make_pair(GL_RGBA16I, GL_RGBA_INTEGER)));
	m_Formats.insert(std::make_pair(RGBA16_UINT,	
					std::make_pair(GL_RGBA16UI, GL_RGBA_INTEGER)));
	m_Formats.insert(std::make_pair(RGBA32_INT,		
					std::make_pair(GL_RGBA32I, GL_RGBA_INTEGER)));
	m_Formats.insert(std::make_pair(RGBA32_UINT,	
					std::make_pair(GL_RGBA32UI, GL_RGBA_INTEGER)));
	m_Formats.insert(std::make_pair(R8_UNORM,
					std::make_pair(GL_R8, GL_RED)));
	m_Formats.insert(std::make_pair(R16_UNORM,
					std::make_pair(GL_R16, GL_RED)));
	m_Formats.insert(std::make_pair(RG8_UNORM,
					std::make_pair(GL_RG8, GL_RG)));
	m_Formats.insert(std::make_pair(RG16_UNORM,
					std::make_pair(GL_RG16, GL_RG)));
	m_Formats.insert(std::make_pair(RGB5A1_UNORM,
					std::make_pair(GL_RGB5_A1, GL_RGB)));
	m_Formats.insert(std::make_pair(RGBA8_UNORM,
					std::make_pair(GL_RGBA8, GL_RGBA)));
	m_Formats.insert(std::make_pair(RGB10A2_UNORM,
					std::make_pair(GL_RGB10_A2, GL_RGBA)));
	m_Formats.insert(std::make_pair(RGBA16_UNORM,
					std::make_pair(GL_RGBA16, GL_RGBA)));
	m_Formats.insert(std::make_pair(RGBA8_SRGB_UNORM,
					std::make_pair(GL_SRGB8_ALPHA8, GL_RGBA)));
	m_Formats.insert(std::make_pair(D24_S8,
					std::make_pair(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL)));

	return true;
}

CTexture* COGLGraphicsAPI::createTexture(int width,
	int height,
	TEXTURE_BINDINGS binding,
	TEXTURE_FORMATS format)
{
	COGLTexture* Tex = new COGLTexture();
	//Create texture
	if (binding & RENDER_TARGET)
	{
		glGenFramebuffers(1, &Tex->m_iFramebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, Tex->m_iFramebuffer);
	}
	if (binding & SHADER_RESOURCE)
	{
		glGenTextures(1, &Tex->m_iTexture);
		glBindTexture(GL_TEXTURE_2D, Tex->m_iTexture);
		glTexImage2D(GL_TEXTURE_2D,
			0,
			m_Formats[format].first,
			width,
			height,
			0,
			m_Formats[format].second,
			GL_UNSIGNED_BYTE,
			NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (Tex->m_iFramebuffer != 0)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_2D,
				Tex->m_iTexture,
				0);
		}
	}	
	if (binding & DEPTH_STENCIL)
	{
		//Create RenderBufferObject for depth and stencil
		glGenRenderbuffers(1, &Tex->m_iTexture);
		glBindRenderbuffer(GL_RENDERBUFFER, Tex->m_iTexture);
		glRenderbufferStorage(GL_RENDERBUFFER, m_Formats[format].first, width, height);
	}
	return Tex;
}

CShaderProgram* COGLGraphicsAPI::createShaderProgram(std::wstring vsfile,
	std::wstring psfile)
{
	const char* source;
	int result;
	char log[512];
	source = readShaderFile(vsfile);

	COGLShaderProgram* ShaderProgram = new COGLShaderProgram();
	COGLVertexShader* VS =
		dynamic_cast<COGLVertexShader*>(ShaderProgram->getVertexShader());
	COGLPixelShader* PS = 
		dynamic_cast<COGLPixelShader*>(ShaderProgram->getPixelShader());

	VS->m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VS->m_VertexShader, 1, &source, NULL);
	glCompileShader(VS->m_VertexShader);

	glGetShaderiv(VS->m_VertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(VS->m_VertexShader, 512, NULL, log);
		OutputDebugStringA(log);
		delete ShaderProgram;
		return nullptr;
	}

	source = readShaderFile(psfile);
	
	PS->m_PS = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(PS->m_PS, 1, &source, NULL);
	glCompileShader(PS->m_PS);

	glGetShaderiv(PS->m_PS, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(PS->m_PS, 512, NULL, log);
		OutputDebugStringA(log);
		delete ShaderProgram;
		return nullptr;
	}

	ShaderProgram->m_Program = glCreateProgram();
	glAttachShader(ShaderProgram->m_Program, VS->m_VertexShader);
	glAttachShader(ShaderProgram->m_Program, PS->m_PS);
	glLinkProgram(ShaderProgram->m_Program);

	glGetProgramiv(ShaderProgram->m_Program, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(ShaderProgram->m_Program, 512, NULL, log);
		OutputDebugStringA(log);
		delete ShaderProgram;
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

void COGLGraphicsAPI::drawIndexed(unsigned int indices)
{
	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
}

void COGLGraphicsAPI::clearBackBuffer(float red, float green, float blue)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void COGLGraphicsAPI::setInputLayout(CInputLayout* layout)
{
	glBindVertexArray(dynamic_cast<COGLInputLayout*>(layout)->VAO);
}

void COGLGraphicsAPI::setRenderTarget(CTexture* texture, CTexture* depth)
{
	if (texture)
	{
		COGLTexture* tex = dynamic_cast<COGLTexture*>(texture);
		if (tex->m_iFramebuffer != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, tex->m_iFramebuffer);
			if (depth)
			{
				COGLTexture* d = dynamic_cast<COGLTexture*>(depth);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER,
					GL_DEPTH_STENCIL_ATTACHMENT,
					GL_RENDERBUFFER,
					d->m_iTexture);
			}
			else
			{
				glFramebufferRenderbuffer(GL_FRAMEBUFFER,
					GL_DEPTH_STENCIL_ATTACHMENT,
					GL_RENDERBUFFER,
					0);
			}
		}
		else
		{
			OutputDebugStringA("Invalid RenderTargetView.");
		}		
	}
	else
	{
		OutputDebugStringA("Received null pointer for texture.");
	}
}

void COGLGraphicsAPI::updateBuffer(CBuffer* buffer, const void* data)
{
	if (!buffer)
	{
		OutputDebugStringA("Invalid buffer received.");
		return;
	}
	if (!data)
	{
		OutputDebugStringA("Invalid data received.");
		return;
	}

	COGLBuffer* buff = dynamic_cast<COGLBuffer*>(buffer);
	if (buff->m_Buffer == 0)
	{
		OutputDebugStringA("Buffer not initalized, can't update data.");
		return;
	}
	glBindBuffer(buff->m_Type, buff->m_Buffer);
	glBufferSubData(buff->m_Type, 0, buff->m_Size, data);
	glBindBuffer(buff->m_Type, 0);
}

CBuffer* COGLGraphicsAPI::createBuffer(const void* data,
	unsigned int size,
	BUFFER_TYPE type)
{
	if (size != 0)
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
			OGLBuffer->m_Type = GL_UNIFORM_BUFFER;
			break;
		}

		glBindBuffer(OGLBuffer->m_Type, OGLBuffer->m_Buffer);

		if (data != nullptr)
		{			
			glBufferData(OGLBuffer->m_Type, OGLBuffer->m_Size, data, GL_STATIC_DRAW);
		}	
		else
		{
			glBufferData(OGLBuffer->m_Type, OGLBuffer->m_Size, nullptr, GL_STATIC_DRAW);
		}

		glBindBuffer(OGLBuffer->m_Type, 0);
		return OGLBuffer;
	}
	else
	{
		OutputDebugStringA("Invalid size for buffer");
		return nullptr;
	}	
}

CInputLayout* COGLGraphicsAPI::createInputLayout(CShaderProgram* program, LAYOUT_DESC desc)
{
	COGLInputLayout* ILayout = new COGLInputLayout();
	glBindVertexArray(ILayout->VAO);
	int size = 0;
	for (int i = 0; i < desc.v_Layout.size(); i++)
	{
		switch (desc.v_Layout[i].s_Format)
		{
		case VEC_F:
			size = 1;
			break;
		case VEC_2F:
			size = 2;
			break;
		case VEC_3F:
			size = 3;
			break;
		case VEC_4F:
			size = 4;
			break;
		}

		glVertexAttribFormat(i, size, GL_FLOAT, GL_FALSE, desc.v_Layout[i].s_Offset);
		glVertexAttribBinding(i, 0);
		glEnableVertexAttribArray(i);
	}
	glBindVertexArray(0);
	return ILayout;
}