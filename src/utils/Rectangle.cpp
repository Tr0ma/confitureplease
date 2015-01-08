#include "Rectangle.h"

void Rectangle::SetTo(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

float Rectangle::GetRight()
{
	return m_X + m_Width;
}

float Rectangle::GetBottom()
{
	return m_Y + m_Height;
}
