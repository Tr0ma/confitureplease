#ifndef _TEXTURE_H_
#define _TEXTURE_H_


class Texture
{
protected:
	int		m_Width;
	int		m_Height;

public:
	int GetWidth()	{ return m_Width; }
	int GetHeight() { return m_Height; }

public:
	explicit Texture() {}
	virtual ~Texture() {}

	Texture* GetBase() { return nullptr; }
};

#endif