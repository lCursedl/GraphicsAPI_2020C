#pragma once

enum BUFFER_TYPE
{
	VERTEX_BUFFER,
	INDEX_BUFFER,
	CONST_BUFFER
};

class CBuffer
{
public:
	CBuffer() {}
	~CBuffer() {}

	virtual void init(unsigned int size, BUFFER_TYPE type) = 0;
	virtual void clear() = 0;
};