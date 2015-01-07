#include "Rectangle.h"

void Rectangle::SetTo(int x, int y, int width, int height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

int Rectangle::GetRight()
{
	return m_X + m_Width;
}

int Rectangle::GetBottom()
{
	return m_Y + m_Height;
}
