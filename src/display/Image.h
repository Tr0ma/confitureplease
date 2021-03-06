#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "RenderSupport.h"
#include "Rectangle.h"

class Texture;

class Image : public DisplayObject
{
private:
	Texture*		m_Texture;
	vector<Vec2d>	m_Vertex;

public:
	Texture&	GetTexture()				{ return *m_Texture; }
	void		SetTexture(Texture& value)	{ m_Texture = &value; }

public:
	explicit Image(Texture& texture);
	virtual ~Image() {}

	virtual Rectangle&	GetBounds(DisplayObject& target, Rectangle& resultRect) override;
	virtual void		Render(RenderSupport& renderSupport, float parentAlpha) override;
};

#endif