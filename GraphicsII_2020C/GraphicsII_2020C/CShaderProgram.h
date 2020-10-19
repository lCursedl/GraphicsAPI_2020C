#pragma once
#include "CShader.h"

class CShaderProgram
{
public:
	CShaderProgram() {}
	virtual ~CShaderProgram() 
	{
		clear();
	}

	virtual void clear()
	{
		m_pVertexShader->clear();
		m_pPixelShader->clear();
	}

	CVertexShader* getVertexShader()
	{
		return m_pVertexShader;
	}
	CPixelShader* getPixelShader()
	{
		return m_pPixelShader;
	}

protected:

	CVertexShader* m_pVertexShader = nullptr;
	CPixelShader* m_pPixelShader = nullptr;
};