#ifndef _MOVECOMPLETEEVENT_H_
#define _MOVECOMPLETEEVENT_H_
#include <Event.h>

class MoveCompleteEvent : public Event
{
public:
	static const char* TYPE;

public:
	explicit MoveCompleteEvent() : Event(TYPE){}
	~MoveCompleteEvent() {}
};

#endif