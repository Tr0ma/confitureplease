#ifndef _SWAPCONFIRMEDEVENT_H_
#define _SWAPCONFIRMEDEVENT_H_
#include <Event.h>
#include <vector>

using namespace std;

class GemVO;

class SwapConfirmedEvent : public Event
{
public:
	static const char* TYPE;

	GemVO&				m_GemA;
	GemVO&				m_GemB;
	vector<GemVO*>&		m_GemList;

public:
	explicit SwapConfirmedEvent(GemVO& gemA, GemVO& gemB, vector<GemVO*>& list) 
		: Event(TYPE), m_GemA(gemA), m_GemB(gemB), m_GemList(list) {}
	~SwapConfirmedEvent() {}
};

#endif