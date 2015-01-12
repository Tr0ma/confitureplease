#ifndef _PATTERNSFOUNDEVENT_H_
#define _PATTERNSFOUNDEVENT_H_
#include <Event.h>

class PatternsFoundEvent : public Event
{
public:
	static const char* TYPE;

public:
	explicit PatternsFoundEvent() : Event(TYPE){}
	~PatternsFoundEvent() {}
};

#endif