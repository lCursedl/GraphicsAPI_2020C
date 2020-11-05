#pragma once

enum BUFFER_TYPE
{
	VERTEX_BUFFER = 0x1L,
	INDEX_BUFFER = 0x2L,
	CONST_BUFFER = 0x4L
};

class CBuffer
{
public:
	CBuffer() {}
	virtual ~CBuffer() {}
};