#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

class Rectangle
{
public:
	float m_X;
	float m_Y;
	float m_Width;
	float m_Height;

public:
	explicit Rectangle(float x = 0, float y = 0, float width = 0, float height = 0) 
		: m_X(x), m_Y(y), m_Width(width), m_Height(height) {}

	void SetTo(float x, float y, float width, float height);

	float GetRight();
	float GetBottom();

	~Rectangle() {}
};

#endif
