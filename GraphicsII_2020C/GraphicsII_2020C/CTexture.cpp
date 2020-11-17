#include "CTexture.h"

CTexture::CTexture(){}

CTexture::~CTexture(){}

TEXTURE_BINDINGS operator|(TEXTURE_BINDINGS a, TEXTURE_BINDINGS b)
{
    return static_cast<TEXTURE_BINDINGS>(static_cast<int>(a) | static_cast<int>(b));
}

bool operator&(TEXTURE_BINDINGS a, TEXTURE_BINDINGS b)
{
    return static_cast<int>(a) & static_cast<int>(b);
}

TEXTURE_BINDINGS operator|=(TEXTURE_BINDINGS& a, TEXTURE_BINDINGS b)
{
    a = static_cast<TEXTURE_BINDINGS>(static_cast<int>(a) | static_cast<int>(b));
    return a;
}