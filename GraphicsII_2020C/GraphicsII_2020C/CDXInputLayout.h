#pragma once
#include "CInputLayout.h"
#include <d3d11.h>

/** \class CDXInputLayout
*   \brief Class which holds info for a D3D11's input layout.
*/
class CDXInputLayout :
    public CInputLayout
{
public:
    /** \fn CDXInputLayout()
   *   \brief Class constructor.
   *
   *   Sets m_InputLayout as nullptr.
   */
    CDXInputLayout();
   
    /** \fn ~CDXInputLayout()
    *   \brief Class destructor.
    *
    *   If m_InputLayout was used, release memory before deleting object.
    */
    ~CDXInputLayout();    

private:

    ID3D11InputLayout* m_InputLayout;   /**< ID3D11InputLayout pointer */

    friend class CDXGraphicsAPI;
};