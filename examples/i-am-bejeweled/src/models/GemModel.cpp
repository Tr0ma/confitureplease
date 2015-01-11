#include "GemModel.h"
#include <iostream>

using namespace std;

const char* GemModel::ID = "GemModel_ID";

void GemModel::Register(const char* textureId)
{
	m_List.push_back(textureId);
}

void GemModel::GetListCopy(vector<const char*>& result)
{
	result.clear();
	int l = m_List.size();
	for (int i = 0 ; i < l ; i++)
	{
		result.push_back(m_List[i]);
	}
}