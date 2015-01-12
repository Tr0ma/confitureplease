#ifndef _SWAPCONFIRMEDEVENT_H_
#define _SWAPCONFIRMEDEVENT_H_
#include <Event.h>

class SwapConfirmedEvent : public Event
{
public:
	static const char* TYPE;

public:
	explicit SwapConfirmedEvent() : Event(TYPE){}
	~SwapConfirmedEvent() {}
};

#endif