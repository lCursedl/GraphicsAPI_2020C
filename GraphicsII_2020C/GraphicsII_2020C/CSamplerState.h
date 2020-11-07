#pragma once

enum FILTER_LEVEL
{
	FILTER_POINT,
	FILTER_LINEAR
};

enum WRAPPING
{
	WRAP = 1,
	MIRROR,
	CLAMP,
	BORDER,
	MIRROR_ONCE
};

enum COMPARISON
{
	NEVER = 1,
	LESS,
	EQUAL,
	LESS_EQUAL,
	GREATER,
	NOT_EQUAL,
	GREATER_EQUAL,
	ALWAYS
};

class CSamplerState
{
public:
	CSamplerState();
	virtual ~CSamplerState();
};