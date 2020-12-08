#pragma once
#include "CShaderProgram.h"
#include "CDXVertexShader.h"
#include "CDXPixelShader.h"

/** \class CDXShaderProgram
*   \brief Class which instantiates the Vertex and Pixel shader pointers
* 
*   Because D3D11 doesn't have the concept of ShaderProgram, functionality of this
*   class is limited
*/
class CDXShaderProgram :
    public CShaderProgram
{
protected:

    /** \fn CDXShaderProgram()
    *   \brief Class constructor
    *   Initializes m_pVertexShader & m_pPixelShader.
    */
    CDXShaderProgram();

    friend class CDXGraphicsAPI;
};