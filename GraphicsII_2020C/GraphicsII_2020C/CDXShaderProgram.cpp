#include "CDXShaderProgram.h"

CDXShaderProgram::CDXShaderProgram()
{
	m_pVertexShader = new CDXVertexShader();
	m_pPixelShader = new CDXPixelShader();
}