#ifndef _SWAPCANCELLEDEVENT_H_
#define _SWAPCANCELLEDEVENT_H_
#include <Event.h>

class GemVO;

class SwapCancelledEvent : public Event
{
public:
	static const char* TYPE;

	GemVO& m_GemA;
	GemVO& m_GemB;

public:
	explicit SwapCancelledEvent(GemVO& gemA, GemVO& gemB) 
		: Event(TYPE), m_GemA(gemA), m_GemB(gemB)  {}

	~SwapCancelledEvent() {}
};

#endif