#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <Iw2D.h>

class Texture
{
protected:
	CIw2DImage&		m_Image;

public:
	virtual int		GetWidth()	{ return static_cast<int>(m_Image.GetWidth()); }
	virtual int		GetHeight() { return static_cast<int>(m_Image.GetHeight()); }
	CIw2DImage&		GetImage()	{ return m_Image; }

public:
	explicit Texture(CIw2DImage& image) : m_Image(image) {}
	virtual ~Texture() {}

	
};

#endif