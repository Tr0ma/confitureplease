#ifndef _SUBTEXTURE_H_
#define _SUBTEXTURE_H_

#include "Texture.h"
#include "Rectangle.h"

class SubTexture : public Texture
{
private:
	Texture&	m_ParentTexture;
	Rectangle	m_Region;

public:
	virtual int		GetX() override			{ return m_Region.m_X; }
	virtual int		GetY() override			{ return m_Region.m_Y; }
	virtual int		GetWidth() override		{ return m_Region.m_Width; }
	virtual int		GetHeight() override	{ return m_Region.m_Height; }

public:
	explicit SubTexture(Texture& parentTexture, Rectangle region) 
		: Texture(parentTexture.GetImage()), m_ParentTexture(parentTexture), m_Region(region) {}
	virtual ~SubTexture() {}
};

#endif