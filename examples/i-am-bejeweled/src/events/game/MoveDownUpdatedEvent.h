#ifndef _MOVEDOWNUPDATEDEVENT_H_
#define _MOVEDOWNUPDATEDEVENT_H_
#include <Event.h>

class MoveDownUpdatedEvent : public Event
{
public:
	static const char* TYPE;

public:
	explicit MoveDownUpdatedEvent() : Event(TYPE){}
	~MoveDownUpdatedEvent() {}
};

#endif