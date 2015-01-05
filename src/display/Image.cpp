#include "Image.h"

void Image::Render(RenderSupport& renderSupport, float parentAlpha)
{
	renderSupport.DrawImage(*this, parentAlpha);
}