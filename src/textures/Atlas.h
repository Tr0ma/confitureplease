#ifndef _ATLAS_H_
#define _ATLAS_H_

#include "Texture.h"
#include "SubTexture.h"
#include <vector>

using namespace std;

class Atlas
{
	class SubTextureItem
	{
	public:
		const char*		m_Name;
		SubTexture&		m_SubTexture;

	public:
		explicit SubTextureItem(const char* name, SubTexture& texture) 
			: m_Name(name), m_SubTexture(texture) {}
	};

private:
	Texture&				m_AtlasTexture;
	vector<SubTextureItem*> m_SubTextures;

public:
	explicit Atlas(Texture& atlasTexture, const char* atlasData) : m_AtlasTexture(atlasTexture) {};
	virtual ~Atlas() {};

	Texture& GetTexture(const char* name);

private:
	void ParseAtlas(const char* atlasData);
	void AddRegion(const char* name, Rectangle region);
};

#endif