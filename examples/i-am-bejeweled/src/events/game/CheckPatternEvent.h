#ifndef _CHECKPATTERNEVENT_H_
#define _CHECKPATTERNEVENT_H_
#include <Event.h>

class CheckPatternEvent : public Event
{
public:
	static const char* TYPE;

public:
	explicit CheckPatternEvent() : Event(TYPE){}
	~CheckPatternEvent() {}
};

#endif