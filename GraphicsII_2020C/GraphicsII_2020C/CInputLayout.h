#pragma once
#include <string>
#include <vector>

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
	LAYOUT(SEMANTIC s, FORMAT f, int offset)
	{
		s_Semantic = s;
		s_Format = f;
		s_Offset = offset;
	}
	SEMANTIC s_Semantic;
	FORMAT s_Format;
	int s_Offset;
};

struct LAYOUT_DESC
{
	void addToDesc(SEMANTIC semantic, FORMAT format, int offset)
	{
		LAYOUT L(semantic, format, offset);
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