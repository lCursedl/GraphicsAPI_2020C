#pragma once
#include "CBuffer.h"
#include <d3d11.h>

/** \class CDXBuffer
*   \brief Class which holds info for a D3D11's buffer.
*/
class CDXBuffer :
    public CBuffer
{
public:   
   
    /** \fn ~CDXBuffer()
    *   \brief Class destructor
    *
    *   If m_Buffer was used, release memory before deleting object
    */
    ~CDXBuffer();

protected:

    /** \fn CDXBuffer()
   *   \brief Class constructor
   *
   *   Sets m_Buffer as nullptr.
   */
    CDXBuffer();
private:

    ID3D11Buffer* m_Buffer;     /**< ID3D11Buffer pointer */

    friend class CDXGraphicsAPI;
};