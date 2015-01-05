#include "SubTexture.h"


SubTexture::SubTexture(CIw2DImage& image, Rectangle region) : Texture(image), m_Region(region)
{
}