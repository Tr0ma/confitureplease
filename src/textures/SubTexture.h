#ifndef _SUBTEXTURE_H_
#define _SUBTEXTURE_H_

#include "Texture.h"
#include "Rectangle.h"

class SubTexture : public Texture
{
private:
	Rectangle	m_Region;

public:
	virtual int		GetWidth() override		{ return m_Region.m_Width; }
	virtual int		GetHeight() override	{ return m_Region.m_Height; }

public:
	explicit SubTexture(CIw2DImage& image, Rectangle region);
	virtual ~SubTexture() {}
};

#endif