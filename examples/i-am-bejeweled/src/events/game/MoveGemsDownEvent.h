#ifndef _MOVEGEMSDOWNEVENT_H_
#define _MOVEGEMSDOWNEVENT_H_
#include <Event.h>

class MoveGemsDownEvent : public Event
{
public:
	static const char* TYPE;

public:
	explicit MoveGemsDownEvent() : Event(TYPE){}
	~MoveGemsDownEvent() {}
};

#endif