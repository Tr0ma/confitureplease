#ifndef _GESTUREEVENT_H_
#define _GESTUREEVENT_H_

#include "EventDispatcher.h"

class GestureEvent : public Event
{
public:
	static const char* GESTURE_RECOGNIZED;

public:
	explicit GestureEvent(const char* type) : Event(type) {}
	~GestureEvent() {};
};

#endif