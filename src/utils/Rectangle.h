#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

class Rectangle
{
public:
	int m_X;
	int m_Y;
	int m_Width;
	int m_Height;

public:
	explicit Rectangle(int x = 0, int y = 0, int width = 0, int height = 0) 
		: m_X(x), m_Y(y), m_Width(width), m_Height(height) {}

	void SetTo(int x, int y, int width, int height);

	int GetRight();
	int GetBottom();

	~Rectangle() {}
};

#endif
