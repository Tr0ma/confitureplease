#include "Image.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include <MatrixUtil.h>

Image::Image(Texture& texture) : m_Texture(texture)
{
	int width = texture.GetWidth();
	int height = texture.GetHeight();

	m_Vertex.push_back(Vec2d(0, 0));
	m_Vertex.push_back(Vec2d(width, 0));
	m_Vertex.push_back(Vec2d(0, height));
	m_Vertex.push_back(Vec2d(width, height));
}

Rectangle& Image::GetBounds(DisplayObject& target, Rectangle& resultRect)
{
	if (&target == dynamic_cast<DisplayObject*>(this))
	{
		helperVec2d = m_Vertex[3];
		resultRect.SetTo(0, 0, helperVec2d.x, helperVec2d.y);
	}
	else if (&target == dynamic_cast<DisplayObject*>(GetParent()))
	{
		float scaleX = GetScaleX();
		float scaleY = GetScaleY();
		helperVec2d = m_Vertex[3];
		resultRect.SetTo(
			GetX() - GetPivotX() * scaleX,
			GetY() - GetPivotY() * scaleY,
			helperVec2d.x * scaleX,
			helperVec2d.y * scaleY
			);

		if (scaleX < 0)
		{
			resultRect.m_Width *= - 1;
			resultRect.m_X -= resultRect.m_Width;
		}

		if (scaleY < 0)
		{
			resultRect.m_Height *= - 1;
			resultRect.m_Y -= resultRect.m_Height;
		}
	}
	else
	{
		GetRelativeTransformationMatrix(&target, helperMatrix);
		long minX = INT_MAX;
		long minY = INT_MAX;
		long maxX = -INT_MAX;
		long maxY = -INT_MAX;

		for (int i = 0 ; i < 4 ; i++)
		{
			int x = m_Vertex[i].x;
			int y = m_Vertex[i].y;

			MatrixUtil::TransformCoords(helperMatrix, x, y, helperVec2d);

			if (minX > helperVec2d.x) minX = helperVec2d.x;
			if (maxX < helperVec2d.x) maxX = helperVec2d.x;
			if (minY > helperVec2d.y) minY = helperVec2d.y;
			if (maxY < helperVec2d.y) maxY = helperVec2d.y;
		}

		resultRect.SetTo(minX, minY, maxX - minX, maxY - minY);
	}

	return resultRect;
}

void Image::Render(RenderSupport& renderSupport, float parentAlpha)
{
	renderSupport.DrawImage(*this, parentAlpha);
}