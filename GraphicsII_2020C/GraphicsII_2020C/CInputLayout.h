#pragma once
#include <string>
#include <vector>
#include "Formats.h"

/**	\enum SEMANTIC
*	\brief Enum which contains definitions for different shader semantics.
*/
enum SEMANTIC
{
	POSITION,
	TEXCOORD,
	NORMAL,
	BINORMAL,
	TANGENT
};

/**	\enum FORMAT
*	\brief Enum which contains definitions for variable formats.
*/
enum FORMAT
{
	VEC_F,
	VEC_2F,
	VEC_3F,
	VEC_4F
};

/** \struct LAYOUT
*	\brief Structure which contains a single layout element.
*/
struct LAYOUT
{
	LAYOUT(SEMANTIC s, FORMATS f, int offset, int elements)
	{
		s_Semantic = s;
		s_Format = f;
		s_Offset = offset;
		s_NumElements = elements;
	}
	/**	\fn LAYOUT(SEMANTIC s, FORMATS f, int offset, int elements)
	*	\brief Struct constructor
	*	@param[in] s Input SEMANTIC
	*	@param[in] f Input FORMAT
	*	@param[in] offset int with value for the layout offset
	*	@param[in] elements int with value for the amount of elements in layout
	*/

	SEMANTIC s_Semantic;	/**< SEMANTIC member to store semantic type*/
	FORMATS s_Format;		/**< FORMATS member to store format type*/
	int s_Offset;			/**< int member to store layout offset*/
	int s_NumElements;		/**< int member to store number of elements in layout*/
};

/** \struct LAYOUT_DESC
*	\brief Structure which contains a collection of layouts.
*/
struct LAYOUT_DESC
{
	/**	\fn void addToDesc(SEMANTIC semantic, FORMATS format, int offset, int elements)
	*	\brief Create & add a layout element to the collection.
	*	@param[in] semantic Input SEMANTIC.
	*	@param[in] format	Input FORMAT
	*	@param[in] offset	int with value for the layout offset
	*	@param[in] elements	int with value for the amount of elements in layout
	*/
	void addToDesc(SEMANTIC semantic, FORMATS format, int offset, int elements)
	{
		LAYOUT L(semantic, format, offset, elements);
		v_Layout.push_back(L);
	}	

	std::vector<LAYOUT>v_Layout;	/**< vector of LAYOUT's */
};

/**	\class CInputLayout
*	\brief Class which serves as an interface for both CDXInputLayout & COGLInputLayout
* 
*	Contains only a constructor and virtual destructor
*/
class CInputLayout
{
public:
	CInputLayout(){}
	virtual ~CInputLayout(){}
};