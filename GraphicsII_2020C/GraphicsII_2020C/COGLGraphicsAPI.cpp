#include "COGLGraphicsAPI.h"
#include "COGLRTV.h"
#include "COGLTexture.h"
#include "COGLBuffer.h"
#include "COGLShaderProgram.h"
#include "COGLInputLayout.h"
#include "COGLSamplerState.h"
#include "COGLVertexShader.h"
#include "COGLPixelShader.h"
#include <string>
#include <fstream>
#include <sstream>
#include "stb_image.h"

void COGLGraphicsAPI::readShaderFile(std::wstring file, std::string &source)
{
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		shaderFile.open(file);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		source = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		return;
	}
}

void COGLGraphicsAPI::fillFormats()
{
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

	m_Handle = GetDC(window);
	int pixelFormat = ChoosePixelFormat(m_Handle, &pfd);

	SetPixelFormat(m_Handle, pixelFormat, &pfd);

	oglRenderContext = wglCreateContext(m_Handle);
	wglMakeCurrent(m_Handle, oglRenderContext);

	if (!gladLoadGL())
	{
		return false;
	}
	RECT rc;
	GetWindowRect(window, &rc);
	setViewport(rc.right - rc.left, rc.bottom - rc.top);
	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	fillFormats();

	return true;
}

void COGLGraphicsAPI::shutdown()
{
	wglDeleteContext(oglRenderContext);
}

CTexture* COGLGraphicsAPI::createTexture(int width,
	int height,
	TEXTURE_BINDINGS binding,
	FORMATS format)
{
	COGLTexture* Tex = new COGLTexture();
	
	if (binding & TEXTURE_BINDINGS::DEPTH_STENCIL)
	{
		//Create RenderBufferObject for depth and stencil
		glGenRenderbuffers(1, &Tex->m_iTexture);
		glBindRenderbuffer(GL_RENDERBUFFER, Tex->m_iTexture);
		glRenderbufferStorage(GL_RENDERBUFFER, m_Formats[format].first, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	else
	{
		//Create texture
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
		if (binding & TEXTURE_BINDINGS::RENDER_TARGET)
		{
			glGenFramebuffers(1, &Tex->m_iFramebuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, Tex->m_iFramebuffer);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_2D,
				Tex->m_iTexture,
				0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	int a = glGetError();
	return Tex;
}

CTexture* COGLGraphicsAPI::createTextureFromFile(std::string path)
{
	int width, height, components;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &components, 0);
	if (data)
	{
		GLenum format = GL_ZERO;
		if (components == 1)
		{
			format = GL_RED;
		}
		else if (components == 2)
		{
			format = GL_RG;
		}
		else if (components == 3)
		{
			format = GL_RGB;
		}
		else if (components == 4)
		{
			format = GL_RGBA;
		}

		COGLTexture* texture = new COGLTexture();
		glGenTextures(1, &texture->m_iTexture);
		glBindTexture(GL_TEXTURE_2D, texture->m_iTexture);
		glTexImage2D(GL_TEXTURE_2D,
			0,
			format,
			width,
			height,
			0,
			format,
			GL_UNSIGNED_BYTE,
			data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);

		return texture;
	}
	stbi_image_free(data);
	return nullptr;
}

std::wstring getFileNameOGL(std::wstring vsfile)
{
	size_t realPos = 0;
	size_t posInvSlash = vsfile.rfind('\\');
	size_t posSlash = vsfile.rfind('/');

	if (posInvSlash == std::wstring::npos)
	{//No encontramos diagonales invertidas
		if (!posSlash == std::wstring::npos)
		{//Encontramos diagonales normales
			realPos = posSlash;
		}
	}
	else
	{//Encontramos diagonales invertidas
		realPos = posInvSlash;
		if (!posSlash == std::wstring::npos)
		{
			if (posSlash > realPos)
			{
				posSlash = realPos;
			}
		}
	}

	return vsfile.substr(realPos, vsfile.length() - realPos);
}

CShaderProgram* COGLGraphicsAPI::createShaderProgram()
{
	COGLShaderProgram* ShaderProgram = new COGLShaderProgram();
	ShaderProgram->m_Program = glCreateProgram();
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

void COGLGraphicsAPI::clearBackBuffer(COLOR color)
{
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(color.red, color.green, color.blue, color.alpha);
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
				if (d->m_iTexture != 0)
				{
					d->m_iFramebuffer = tex->m_iFramebuffer;
					glFramebufferRenderbuffer(GL_FRAMEBUFFER,
						GL_DEPTH_STENCIL_ATTACHMENT,
						GL_RENDERBUFFER,
						d->m_iTexture);
				}
				else
				{
					OutputDebugStringA("Invalid Depth Stencil received.");
				}				
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
			OutputDebugStringA("Invalid RenderTargetView received.");
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

void COGLGraphicsAPI::setVertexBuffer(CBuffer* buffer, unsigned int size)
{
	if (buffer != nullptr)
	{
		COGLBuffer* buff = dynamic_cast<COGLBuffer*>(buffer);
		if (buff->m_Buffer != 0)
		{
			glBindVertexBuffer(0, buff->m_Buffer, 0, size);
		}
		else
		{
			OutputDebugStringA("Buffer missing initialization.");
		}
	}
	else
	{
		OutputDebugStringA("Empty buffer received.");
	}
}

void COGLGraphicsAPI::setIndexBuffer(CBuffer* buffer)
{
	if (buffer != nullptr)
	{
		COGLBuffer* buff = dynamic_cast<COGLBuffer*>(buffer);
		if (buff->m_Buffer != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buff->m_Buffer);
		}
		else
		{
			OutputDebugStringA("Buffer missing initialization.");
		}
	}
	else
	{
		OutputDebugStringA("Empty buffer received.");
	}
}

void COGLGraphicsAPI::setSamplerState(unsigned int slot,
	CTexture* texture,
	CSamplerState* sampler)
{
	if (!texture)
	{
		OutputDebugStringA("Invalid texture received.");
		return;
	}
	if (!sampler)
	{
		OutputDebugStringA("Invaid sampler received.");
		return;
	}

	COGLTexture* tex = dynamic_cast<COGLTexture*>(texture);

	if (tex->m_iTexture == 0)
	{
		OutputDebugStringA("Texture missing initialization.");
		return;
	}

	COGLSamplerState* samp = dynamic_cast<COGLSamplerState*>(sampler);

	if (samp->m_Sampler == 0)
	{
		OutputDebugStringA("Sampler missing initialization.");
		return;
	}

	glBindSampler(tex->m_iTexture, samp->m_Sampler);
}

void COGLGraphicsAPI::setConstantBuffer(unsigned int slot,
	CBuffer* buffer,
	SHADER_TYPE shaderType)
{
	if (buffer)
	{
		COGLBuffer* buff = dynamic_cast<COGLBuffer*>(buffer);
		if (buff->m_Buffer != 0)
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, slot, buff->m_Buffer);
		}
		else
		{
			OutputDebugStringA("Buffer not initialized received.");
		}
	}
	else
	{
		OutputDebugStringA("Invalid buffer received.");
	}
}

void COGLGraphicsAPI::clearRenderTarget(CTexture* rt, COLOR color)
{
	if (!rt)
	{
		OutputDebugStringA("Invalid Render Target received.");
		return;
	}
	COGLTexture* tex = dynamic_cast<COGLTexture*>(rt);
	if (tex->m_iFramebuffer == 0)
	{
		OutputDebugStringA("Render target not initialized received.");
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, tex->m_iFramebuffer);
	glClearColor(color.red, color.green, color.blue, color.alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void COGLGraphicsAPI::clearDepthStencil(CTexture* ds)
{
	if (!ds)
	{
		OutputDebugStringA("Invalid Depth Stencil received.");
		return;
	}
	COGLTexture* depth = dynamic_cast<COGLTexture*>(ds);
	if (depth->m_iTexture == 0 || depth->m_iFramebuffer == 0)
	{
		OutputDebugStringA("Depth Stencil not initialized received.");
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, depth->m_iFramebuffer);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void COGLGraphicsAPI::setTexture(unsigned int slot, CTexture* texture)
{
	COGLTexture* tex = dynamic_cast<COGLTexture*>(texture);
	if (!tex)
	{
		OutputDebugStringA("Texture received was nullptr.");
		return;
	}
	if (tex->m_iTexture == 0)
	{
		OutputDebugStringA("Uninitialized texture received.");
		return;
	}
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, tex->m_iTexture);
}

void COGLGraphicsAPI::swapBuffer()
{
	SwapBuffers(m_Handle);
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
	glGenVertexArrays(1, &ILayout->VAO);
	glBindVertexArray(ILayout->VAO);
	for (int i = 0; i < desc.v_Layout.size(); i++)
	{
		glVertexAttribFormat(i,
			desc.v_Layout[i].s_NumElements,
			GL_FLOAT, GL_FALSE,
			desc.v_Layout[i].s_Offset);
		glVertexAttribBinding(i, 0);
		glEnableVertexAttribArray(i);
	}
	glBindVertexArray(0);
	return ILayout;
}

CSamplerState* COGLGraphicsAPI::createSamplerState(FILTER_LEVEL mag,
	FILTER_LEVEL min,
	FILTER_LEVEL mip,
	unsigned int anisotropic,
	WRAPPING wrapMode)
{
	COGLSamplerState* sampler = new COGLSamplerState();

	glGenSamplers(1, &sampler->m_Sampler);
	
	int mode;

	switch (wrapMode)
	{
	case WRAP:
		mode = GL_REPEAT;
		break;
	case MIRROR:
		mode = GL_MIRRORED_REPEAT;
		break;
	case CLAMP:
		mode = GL_CLAMP_TO_EDGE;
		break;
	case BORDER:
		mode = GL_CLAMP_TO_BORDER;
	case MIRROR_ONCE:
		mode = GL_MIRROR_CLAMP_TO_EDGE;
		break;
	}


	glSamplerParameteri(sampler->m_Sampler,
		GL_TEXTURE_WRAP_S, mode);
	glSamplerParameteri(sampler->m_Sampler,
		GL_TEXTURE_WRAP_T, mode);

	if (anisotropic > 0)
	{
		if (anisotropic > GL_MAX_TEXTURE_MAX_ANISOTROPY)
		{
			anisotropic = GL_MAX_TEXTURE_MAX_ANISOTROPY;
		}
		glSamplerParameterf(sampler->m_Sampler, GL_TEXTURE_MAX_ANISOTROPY, anisotropic);

	}
	
	int maglevel;
	switch (mag)
	{
	case FILTER_POINT:
		maglevel = GL_NEAREST;
		break;
	case FILTER_LINEAR:
		maglevel = GL_LINEAR;
		break;
	}

	glSamplerParameteri(sampler->m_Sampler, GL_TEXTURE_MAG_FILTER, maglevel);

	int minmipLevel;
	if (min == FILTER_POINT)
	{
		if (mip == FILTER_POINT)
		{
			minmipLevel = GL_NEAREST_MIPMAP_NEAREST;
		}
		else
		{
			minmipLevel = GL_NEAREST_MIPMAP_LINEAR;
		}
	}
	else if (min == FILTER_LINEAR)
	{
		if (mip == FILTER_LINEAR)
		{
			minmipLevel = GL_LINEAR_MIPMAP_NEAREST;
		}
		else
		{
			minmipLevel = GL_LINEAR_MIPMAP_LINEAR;
		}
	}

	glSamplerParameteri(sampler->m_Sampler, GL_TEXTURE_MIN_FILTER, minmipLevel);

	return sampler;
}

CVertexShader* COGLGraphicsAPI::createVertexShader(std::wstring file)
{
	std::wstring realFileName = getFileNameOGL(file) + L"_OGL.glsl";
	std::string source;
	int result;
	char log[512];
	readShaderFile(realFileName, source);
	const char* vs_Source = source.c_str();

	COGLVertexShader* vs = new COGLVertexShader();
	vs->m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs->m_VertexShader, 1, &vs_Source, 0);
	glCompileShader(vs->m_VertexShader);

	glGetShaderiv(vs->m_VertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vs->m_VertexShader, 512, 0, log);
		OutputDebugStringA(log);
		delete vs;
		return nullptr;
	}
	return vs;
}

CPixelShader* COGLGraphicsAPI::createPixelShader(std::wstring file)
{
	std::wstring realFileName = getFileNameOGL(file) + L"_OGL.glsl";
	std::string source;
	int result;
	char log[512];
	readShaderFile(realFileName, source);
	const char* ps_Source = source.c_str();

	COGLPixelShader* ps = new COGLPixelShader();
	ps->m_PS = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ps->m_PS, 1, &ps_Source, 0);
	glCompileShader(ps->m_PS);

	glGetShaderiv(ps->m_PS, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(ps->m_PS, 512, 0, log);
		OutputDebugStringA(log);
		delete ps;
		return nullptr;
	}
	return ps;
}