#ifndef _SCREENMANAGEREVENT_H_
#define _SCREENMANAGEREVENT_H_

#include "Event.h"

class ScreenManagerEvent : public Event
{
public:
	static const char* TRANSITION_COMPLETE;

public:
	explicit ScreenManagerEvent(const char* type) : Event(type) {}
	virtual ~ScreenManagerEvent() {}	
};

#endif