#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "RenderSupport.h"

class Texture;

class Image : public DisplayObject
{
private:
	Texture& m_Texture;

public:
	Texture& GetTexture() { return m_Texture; }

public:
	explicit Image(Texture& texture) : m_Texture(texture) {}
	virtual ~Image() {}

	virtual void Render(RenderSupport& renderSupport, float parentAlpha) override;
};

#endif