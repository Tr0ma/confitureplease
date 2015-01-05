#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#include "Atlas.h"
#include <vector>

using namespace std;

class AssetManager
{
	class AtlasItem
	{
	public:
		const char* m_Name;
		Atlas&		m_Atlas;

	public:
		explicit AtlasItem(const char* name, Atlas& atlas) 
			: m_Name(name), m_Atlas(atlas) {}
	};

private:
	vector<AtlasItem*> m_Atlases;

public:
	AssetManager() {}
	~AssetManager();

	void	AddAtlas(const char* name, const char* imagePath, const char* dataPath);
	Atlas*	GetTextureAtlas(const char* name);

};

#endif