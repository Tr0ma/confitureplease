#ifndef _SWAPCANCELLEDEVENT_H_
#define _SWAPCANCELLEDEVENT_H_
#include <Event.h>

class SwapCancelledEvent : public Event
{
public:
	static const char* TYPE;

public:
	explicit SwapCancelledEvent() : Event(TYPE){}
	~SwapCancelledEvent() {}
};

#endif