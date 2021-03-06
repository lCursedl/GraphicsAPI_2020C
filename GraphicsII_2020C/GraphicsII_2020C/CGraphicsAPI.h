#pragma once                                                                             
#include <windows.h>
#include "CTexture.h"
#include "CShader.h"
#include "CBuffer.h"
#include "CShaderProgram.h"
#include "CInputLayout.h"
#include "CSamplerState.h"

#include <string>
#include <map>

#include <glm/vec2.hpp>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"

/** \struct COLOR
*	\brief Structure which defines a color with Red, Green, Blue and Alpha components.
*/
struct COLOR
{
	float red;
	float green;
	float blue;
	float alpha;
};

/**	\enum TOPOLOGY
*	\brief Enum which defines the different types of topologies available from the api.
*/
enum class TOPOLOGY
{
	POINTS,
	LINES,
	TRIANGLES,
	LINE_STRIP,
	TRIANGLE_STRIP,
	LINE_ADJACENCY,
	TRIANGLE_ADJANCENCY,
	LINE_STRIP_ADJACENCY,
	TRIANGLE_STRIP_ADJACENCY
};

/**	\class CGraphicsAPI
*	\brief Class which serves as an interface for CDXGraphicsAPI & COGLGraphicsAPI.
*/
class CGraphicsAPI
{
public:

	/**	\fn bool init(HWND window)
	*	\brief Initializes and creates the necesary elements for basic rendering.
	*	@param[in] window HWND properly created for use.	
	*/
	virtual bool init(HWND window) = 0;

	/** \fn void shutdown()
	*	\brief Releases memory and deletes all resources created by the API.
	*/
	virtual void shutdown() = 0;

	/** \fn glm::mat4 matrix4Policy(const glm::mat4 & mat)
	*	\brief Returns an API compatible matrix of 4 x 4 dimensions
	*	@param[in] mat A glm::mat4 to make compatible.
	*	\return The received matrix in the correct order.
	*/
	virtual glm::mat4 matrix4Policy(const glm::mat4 & mat) = 0;

	/***********************************************************************************/
	/*----------------------------------DEVICE-----------------------------------------*/
	/***********************************************************************************/
	
	/** \fn CTexture* createTexture(int width, int height,
	*								TEXTURE_BINDINGS binding, FORMATS format)
	*	\brief Creates a texture with the received parameters and returns it.
	*	@param[in] width	Specificates texture's width.
	*	@param[in] height	Specificates texture's height.
	*	@param[in] binding	Specifies type of texture to create.
	*	@param[in] format	Specifies the texture format.
	*	\return CTexture pointer of the corresponding API.
	*/
	virtual CTexture* createTexture(int width,
		int height,
		TEXTURE_BINDINGS binding,
		FORMATS format) = 0;

	/**	\fn CTexture* createTextureFromFile(std::string path)
	*	\brief Loads a texture file and returns a CTexture pointer with its data.
	*	@param[in] path The path to the file.
	*	\return CTexture pointer for the corresponding API with data.
	*/
	virtual CTexture* createTextureFromFile(std::string path) = 0;

	/**	\fn CShaderProgram* createShaderProgram()
	*	\brief Creates a shader program and returns it.
	*	\return CShaderProgram pointer of the corresponding API.
	*/
	virtual CShaderProgram* createShaderProgram() = 0;

	/** \fn CBuffer* createBuffer(const void * data, unsigned int size, BUFFER_TYPE type)
	*	\brief Creates a buffer with the received parameters and optionally data.
	*	@param[in] data Pointer to the data to load. Can be nullptr.
	*	@param[in] size Size of the data to load.
	*	@param[in] type	Type of buffer to create (VERTEX_BUFFER,
	*	INDEX_BUFFER, CONST_BUFFER).
	*	\return CBuffer pointer of the corresponding API.
	*/
	virtual CBuffer* createBuffer(const void* data,
		unsigned int size,
		BUFFER_TYPE type) = 0;

	/**	\fn CInputLayout* createInputLayout(CShaderProgram* program, LAYOUT_DESC desc)
	*	\brief Creates an input layout from a descriptor and shader program.
	*	@param[in] program ShaderProgram from where to extract info.
	*	@param[in] desc The layout descriptor.
	*	\return CInputLayout pointer of the corresponding API.
	*/
	virtual CInputLayout* createInputLayout(CShaderProgram* program,
		LAYOUT_DESC desc) = 0;

	/** \fn CSamplerState* createSamplerState(FILTER_LEVEL mag, FILTER_LEVEL min,
	*										  FILTER_LEVEL mip, unsigned int anisotropic
	*										  , WRAPPING wrapMode)
	*	\brief Creates a sampler state from defined parameters and returns it.
	*	@param[in] mag Magnification filter ( LINEAR, POINT ).
	*	@param[in] min Minification filter ( LINEAR, POINT ).
	*	@param[in] mip Mipmap filter ( LINEAR, POINT ).
	*	@param[in] anisotropic Anisotropic level ( 0 - 16 ).
	*	@param[in] wrapMode Mode in which texture border are treated ( WRAP, MIRROR,	
					CLAMP, BORDER, MIRROR_ONCE ).
	*	\return CSamplerState pointer of the corresponding API.
	*/
	virtual CSamplerState* createSamplerState(FILTER_LEVEL mag,
		FILTER_LEVEL min,
		FILTER_LEVEL mip,
		unsigned int anisotropic,
		WRAPPING wrapMode) = 0;

	/**	\fn CVertexShader* createVertexShader(std::wstring file)
	*	\brief Creates a vertex shader from the specified file, if available.
	*	@param[in] file Filename of the vertex shader.
	*	\return CVertexShader pointer of the corresponding API.
	*/
	virtual CVertexShader* createVertexShader(std::wstring file) = 0;

	/**	\fn CPixelShader* createPixelShader(std::wstring file)
	*	\brief Creates a pixe shader from the specified file, if available.
	*	@param[in] file Filename of the pixel shader.
	*	\return CPixelShader pointer of the corresponding API.
	*/
	virtual CPixelShader* createPixelShader(std::wstring file) = 0;

	/***********************************************************************************/
	/*----------------------------DEVICE CONTEXT---------------------------------------*/
	/***********************************************************************************/

	/**	\fn void setBackBuffer()
	*	\brief Sets the default render target view and depth stencil view as current.
	*/
	virtual void setBackBuffer() = 0;

	/**	\fn setViewport(int width, int height)
	*	\brief Sets the viewport area
	*	@param[in] topLeftX Corner on the X axis of the render area.
	*	@param[in] topLeftY Corner on the Y axis of the render area.
	*	@param[in] width Width of render area.
	*	@param[in] height Height of render area.
	*/
	virtual void setViewport(int topLeftX, int topLeftY, int width, int height) = 0;

	/** \fn void drawIndexed(unsigned int indices)
	*	\brief Makes a draw call with the specified amount of indices.
	*	@param[in] indices Amount of indices in geometry to draw.
	*/
	virtual void drawIndexed(unsigned int indices) = 0;

	/**	\fn void draw()
	*	\brief Makes a draw call with the currently bound vertex buffer.
	*	@param[in] count Amount of vertices.
	*	@param[in] first Start location to read the vertices.
	*/
	virtual void draw(unsigned int count, unsigned int first) = 0;

	/** \fn void setShaders(CShaderProgram* program)
	*	\brief Receives a shader program and sets both its vertex and pixel shader
	*	as current.
	*	@param[in] program CShaderProgram pointer from where to take shaders.
	*/
	virtual void setShaders(CShaderProgram* program) = 0;

	/** \fn void setInputLayout(CInputLayout* layout)
	*	\brief Receives an input layout and sets it as current.
	*	@param[in] layout CInputLayout pointer from where to take the layout.
	*/
	virtual void setInputLayout(CInputLayout* layout) = 0;

	/** \fn void clearBackBuffer(COLOR color)
	*	\brief Clears default render target with specified color and depth stencil.
	*	@param[in] color Color in which to clear the render target.
	*/
	virtual void clearBackBuffer(COLOR color) = 0;

	/** void setRenderTarget(CTexture* texture, CTexture* depth)
	*	\brief Sets the specified render target and depth stencil as current.
	*	@param[in] texture CTexture pointer which contains the render target.
	*	@param[in] depth CTexture pointer which contains the depth stencil.
	*	depth can be nullptr if only render target wants to be set.
	*/
	virtual void setRenderTarget(CTexture* texture, CTexture* depth) = 0;

	/** void updateBuffer(CBuffer* buffer, const void * data)
	*	\brief Updates the specified buffer with the received data
	*	@param[in] buffer Buffer to update.
	*	@param[in] data	  Pointer of the data to assign to buffer.
	*/
	virtual void updateBuffer(CBuffer* buffer, const void * data) = 0;

	/** void setVertexBuffer(CBuffer* buffer)
	*	\brief Sets the specified buffer as the current vertex buffer.
	*	@param[in] buffer Buffer to set.
	*	@param[in] stride Lenght of the buffer data.
	*	@param[in] offset Buffer offset from where to take data.
	*	\warning If buffer is nullptr, no operations are done.
	*/
	virtual void setVertexBuffer(CBuffer* buffer,
		unsigned int stride,
		unsigned int offset) = 0;

	/** \fn void setIndexBuffer(CBuffer* buffer)
	*	\brief Sets the specified buffer as the current index buffer.
	*	@param[in] buffer Buffer to set.
	*	\warning If buffer is nullptr, no operations are done.
	*/
	virtual void setIndexBuffer(CBuffer* buffer) = 0;

	/** void setSamplerState(CTexture* texture, CSamplerState* sampler)
	*	\brief Sets the sampler state and binds it to a texture and slot.
	*	@param[in] slot	   Slot of the sampler in the shader.
	*	@param[in] texture Texture to which bind the sampler to.
	*	@param[in] sampler Sampler State to bind.
	*/
	virtual void setSamplerState(unsigned int slot,
		CTexture* texture,
		CSamplerState* sampler) = 0;

	/** \fn void setConstantBuffer(unsigned int slot, CBuffer* buffer,
	*							SHADER_TYPE shaderType)
	*	\brief Sets the specified buffer to use for the shaders.
	*	@param[in] slot Index of the constant buffer in the shader.
	*	@param[in] buffer Buffer to set.
	*	@param[in] shaderType Shader where the buffer is used ( VERTEX_SHADER, 
	*				PIXEL_SHADER )
	*/
	virtual void setConstantBuffer(unsigned int slot,
		CBuffer* buffer,
		SHADER_TYPE shaderType) = 0;

	/** void clearRenderTarget(CTexture* rt, COLOR color)
	*	\brief Clears the specified render target.
	*	@param[in] rt Render target to clear.
	*	@param[in] color COLOR to use for clearing.
	*/
	virtual void clearRenderTarget(CTexture* rt, COLOR color) = 0;

	/** \fn void clearDepthStencil(CTexture* ds)
	*	\brief Clears the specified depth stencil.
	*/
	virtual void clearDepthStencil(CTexture* ds) = 0;

	/**	\fn void setTexture(unsigned int slot, CTexture* texture)
	*	\brief Sets the texture for use in the pixel shader.
	*	@param[in] slot Index of the texture in the shader.
	*	@param[in] texture Texture to set.
	*/
	virtual void setTexture(unsigned int slot, CTexture* texture) = 0;

	/** \fn void setTopology(TOPOLOGY topology)
	*	\brief Sets the topology type for vertex data.
	*	@param[in] topology TOPOLOGY type to set.
	*/
	virtual void setTopology(TOPOLOGY topology) = 0;

	//SWAPCHAIN

	/**	\fn void swapBuffer()
	*	\brief Swaps the back buffer with the front buffer and presents it.
	*/
	virtual void swapBuffer() = 0;

	/** \fn void resizeBackBuffer(unsigned int width, unsigned int height)
	*	\brief Resizes both backbuffer and its depth stencil.
	*	@param[in] width New X dimension for back buffer.
	*	@param[in] height New Y dimension for back buffer.
	*/
	virtual void resizeBackBuffer(unsigned int width, unsigned int height) = 0;
};