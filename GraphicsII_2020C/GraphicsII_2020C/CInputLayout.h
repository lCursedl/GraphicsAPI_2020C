#pragma once
#include <string>
#include <vector>
#include "Formats.h"

enum SEMANTIC
{
	POSITION,
	TEXCOORD,
	NORMAL,
	BINORMAL,
	TANGENT
};

enum FORMAT
{
	VEC_F,
	VEC_2F,
	VEC_3F,
	VEC_4F
};

struct LAYOUT
{
	LAYOUT(SEMANTIC s, FORMATS f, int offset, int elements)
	{
		s_Semantic = s;
		s_Format = f;
		s_Offset = offset;
		s_NumElements = elements;
	}
	SEMANTIC s_Semantic;
	FORMATS s_Format;
	int s_Offset;
	int s_NumElements;
};

struct LAYOUT_DESC
{
	void addToDesc(SEMANTIC semantic, FORMATS format, int offset, int elements)
	{
		LAYOUT L(semantic, format, offset, elements);
		v_Layout.push_back(L);
	}

	std::vector<LAYOUT>v_Layout;
};

class CInputLayout
{
public:
	CInputLayout(){}
	virtual ~CInputLayout(){}
};