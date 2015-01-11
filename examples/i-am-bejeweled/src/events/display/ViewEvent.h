#ifndef _VIEWEVENT_H_
#define _VIEWEVENT_H_
#include <Event.h>

class ViewEvent : public Event
{
public:
	static const char* VIEW_CREATED;
	static const char* VIEW_DESTROYED;
	static const char* VIEW_SHOWN;
	static const char* VIEW_HIDDEN;

public:
	explicit ViewEvent(const char* type) : Event(type) {};
	~ViewEvent() {};
};

#endif
