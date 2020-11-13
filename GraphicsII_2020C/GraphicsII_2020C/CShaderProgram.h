#pragma once
#include "CShader.h"

/**	\class CShaderProgram
*	\brief Class which serves as an interface for both CDXShaderProgram & COGLShaderProgram.
*/
class CShaderProgram
{
public:
	CShaderProgram() {};

	/**	\fn virtual ~CShaderProgram()
	*	\brief Class destructor
	*	
	*	If m_pVertexShader or m_pPixelShader was used, release memory 
		before deleting object.
	*/
	virtual ~CShaderProgram()
	{
		if (m_pVertexShader)
		{
			delete m_pVertexShader;
		}
		if (m_pPixelShader)
		{
			delete m_pPixelShader;
		}
	}

	/**	\fn CVertexShader* getVerteShader()
	*	\brief Obtains the pointer to the VertexShader member
	*	\return	CVertexshader pointer
	*/
	CVertexShader* getVertexShader()
	{
		return m_pVertexShader;
	}

	/** \fn CPixelShader* getPixelShader()
	*	\brief Obtains the pointer to the PixelShader member
	*	\return CPixelShader pointer
	*/
	CPixelShader* getPixelShader()
	{
		return m_pPixelShader;
	}

	/** \fn virtual void setVertexShader(CVertexShader* vertexShader)
	*	\brief Sets the received VS pointer as the one to store.
	*	@param[in] vertexShader CVertexShader pointer to store
	*/
	virtual void setVertexShader(CVertexShader* vertexShader)
	{
		m_pVertexShader = vertexShader;
	}

	/** \fn virtual void setPixelShader(CPixelShader* pixelShader)
	*	\brief Sets the received PS pointer as the one to store.
	*	@param[in] pixelShader CPixelShader pointer to store
	*/
	virtual void setPixelShader(CPixelShader* pixelShader)
	{
		m_pPixelShader = pixelShader;
	}

protected:
	CVertexShader* m_pVertexShader = nullptr;	/**< CVertexShader pointer */
	CPixelShader* m_pPixelShader = nullptr;		/**< CPixelShader pointer */
};