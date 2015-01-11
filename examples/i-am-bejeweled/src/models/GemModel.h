#ifndef _GEMMODEL_H_
#define _GEMMODEL_H_

#include <vector>

using namespace std;

class GemModel
{
public:
	static const char* ID;

private:
	vector<const char*>		m_List;

public:
	vector<const char*>*	GetList()		{ return &m_List; }
	
public:
	GemModel() {}
	~GemModel() {}

	void	Register(const char* textureId);
	void	GetListCopy(vector<const char*>& result);
};

#endif