#pragma once
#include "CShader.h"

class CShaderProgram
{
public:
	CShaderProgram(){}
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

	CVertexShader* getVertexShader()
	{
		return m_pVertexShader;
	}
	CPixelShader* getPixelShader()
	{
		return m_pPixelShader;
	}

	virtual void setVertexShader(CVertexShader* vertexShader)
	{
		m_pVertexShader = vertexShader;
	}

	virtual void setPixelShader(CPixelShader* pixelShader)
	{
		m_pPixelShader = pixelShader;
	}

protected:
	CVertexShader* m_pVertexShader = nullptr;
	CPixelShader* m_pPixelShader = nullptr;
};