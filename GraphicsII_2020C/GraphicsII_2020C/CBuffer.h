#pragma once

enum BUFFER_TYPE
{
	VERTEX_BUFFER = 1,
	INDEX_BUFFER,
	CONST_BUFFER
};

class CBuffer
{
public:
	CBuffer() {}

	virtual ~CBuffer()
	{
		clear();
	}

	virtual void clear(){}
};