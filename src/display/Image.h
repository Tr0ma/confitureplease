#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "RenderSupport.h"

class Texture;

class Image : public DisplayObject
{
private:
	Texture&		m_Texture;
	vector<Vec2d>	m_Vertex;

public:
	Texture& GetTexture() { return m_Texture; }

public:
	explicit Image(Texture& texture);
	virtual ~Image() {}

	virtual Rectangle&	GetBounds(DisplayObject& target, Rectangle& resultRect) override;
	virtual void		Render(RenderSupport& renderSupport, float parentAlpha) override;
};

#endif