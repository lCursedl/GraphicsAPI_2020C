#pragma once
#include "CRTV.h"
#include <glad/glad.h>
class COGLRTV :
    public CRTV
{
public:
    COGLRTV();
    ~COGLRTV();

    void clear()                override;

    unsigned int m_FrameBuffer;
};