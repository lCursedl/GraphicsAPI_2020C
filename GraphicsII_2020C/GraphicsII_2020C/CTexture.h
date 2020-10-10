#pragma once
class CTexture
{
public:
	virtual void init(
		unsigned int Width,
		unsigned int Height,
		unsigned int Miplevels = 0,
		unsigned int ArraySize = 0,
		unsigned int Format = 0,
		unsigned int Count = 0,
		unsigned int Quality = 0,
		unsigned int Usage = 0,
		unsigned int Flags = 0,
		unsigned int CPUAccessFlags = 0,
		unsigned int MiscFlags = 0) = 0;

	virtual void clear() = 0;
};