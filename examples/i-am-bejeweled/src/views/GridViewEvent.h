#ifndef _GRIDVIEWEVENT_H_
#define _GRIDVIEWEVENT_H_
#include <Event.h>

class GridViewEvent : public Event
{
public:
	static const char* SWIPED;

public:
	explicit GridViewEvent(const char* type) : Event(type) {}
	~GridViewEvent() {}
};

#endif