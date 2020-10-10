#include "COGLRTV.h"

COGLRTV::COGLRTV()
{
	m_FrameBuffer = 0;
}

COGLRTV::~COGLRTV()
{
}

void COGLRTV::clear()
{
	glDeleteFramebuffers(1, &m_FrameBuffer);
}
