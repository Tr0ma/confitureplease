#include "Image.h"
#include "DisplayObjectContainer.h"

Image::Image(Texture& texture) : m_Texture(texture)
{
	m_TextureBounds.SetTo(0, 0, texture.GetWidth(), texture.GetHeight());
}

Rectangle Image::GetBounds(DisplayObject* target, Rectangle* resultRect)
{
	if (target == this)
	{
		resultRect->SetTo(m_TextureBounds.m_X, m_TextureBounds.m_Y, 
			m_TextureBounds.m_Width, m_TextureBounds.m_Height);
	}
	else if (target == dynamic_cast<DisplayObject*>(GetParent()))
	{
		float scaleX = GetScaleX();
		float scaleY = GetScaleY();
		resultRect->SetTo(
			GetX() - GetPivotX() * scaleX,
			GetY() - GetPivotY() * scaleY,
			m_TextureBounds.m_Width * scaleX,
			m_TextureBounds.m_Height * scaleY
			);

		if (scaleX < 0)
		{
			resultRect->m_Width *= - 1;
			resultRect->m_X -= resultRect->m_Width;
		}

		if (scaleY < 0)
		{
			resultRect->m_Height *= - 1;
			resultRect->m_Y -= resultRect->m_Height;
		}
	}

	return *resultRect;
}

void Image::Render(RenderSupport& renderSupport, float parentAlpha)
{
	renderSupport.DrawImage(*this, parentAlpha);
}