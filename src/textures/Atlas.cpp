#include "Atlas.h"

Texture& Atlas::GetTexture(const char* name)
{
	const int l = m_SubTextures.size();
	for (int i = 0 ; i < l ; i++)
	{
		SubTextureItem* item = m_SubTextures[i];
		if (item->m_Name == name)
		{
			return item->m_SubTexture;
		}
	}
}