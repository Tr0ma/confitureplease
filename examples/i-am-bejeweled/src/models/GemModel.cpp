#include "GemModel.h"
#include <iostream>

using namespace std;

void GemModel::Register(const char* textureId)
{
	m_List.push_back(textureId);
}

void GemModel::GetListCopy(vector<const char*>& origin, vector<const char*>& target)
{
	target.clear();
	int l = origin.size();
	for (int i = 0 ; i < l ; i++)
	{
		target.push_back(origin[i]);
	}
}