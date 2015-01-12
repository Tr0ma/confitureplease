#ifndef _POOL_H_
#define _POOL_H_

#include <vector>

using namespace std;

template<class C>
class Pool
{
private:
	vector<C*>		m_Available;
	vector<C*>		m_Created;

	int				m_NumAvailable;

public:
	Pool() : m_NumAvailable(0) {}
	~Pool();

	C*		Get();
	void	Release(C* p);
};

template <class C>
Pool<C>::~Pool()
{
	int i = m_Created.size();
	while (--i >= 0)
	{
		delete m_Created[i];
	}

	m_Created.clear();
	m_Available.clear();
}

template <class C>
C* Pool<C>::Get()
{
	if (m_NumAvailable == 0)
	{
		C* p = new C();
		m_Created.push_back(p);

		return p;
	}
	
	return m_Available[m_NumAvailable - 1];
}

template <class C>
void Pool<C>::Release(C* p)
{
	m_Available.push_back(p);
	m_NumAvailable++;
}
#endif
