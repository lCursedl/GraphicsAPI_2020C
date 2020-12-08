#pragma once

/**	\enum FILTER_LEVEL
*	\brief Enum which contains definitions for different filter levels.
*/
enum FILTER_LEVEL
{
	FILTER_POINT,
	FILTER_LINEAR
};

/**	\enum WRAPPING
*	\brief Enum which contains definitions for different wrapping modes.
*/
enum WRAPPING
{
	WRAP = 1,
	MIRROR,
	CLAMP,
	BORDER,
	MIRROR_ONCE
};

/**	\enum COMPARISON
*	\brief Enum which contains definitions for different comparison modes.
*/
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

/**	\class CSamplerState
*	\brief Class which serves as an interface for both CDXSamplerState & COGLSamplerState
* 
*	Contains only a constructor and virtual destructor
*/
class CSamplerState
{
public:
	CSamplerState();
	virtual ~CSamplerState();
};