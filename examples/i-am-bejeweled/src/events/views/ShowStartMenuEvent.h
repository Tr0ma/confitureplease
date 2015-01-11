#ifndef _SHOWSTARTMENUEVENT_H_
#define _SHOWSTARTMENUEVENT_H_
#include <Event.h>

class ShowStartMenuEvent : public Event
{
public:
	static const char* TYPE;

public:
	ShowStartMenuEvent() : Event(TYPE) {};
	~ShowStartMenuEvent() {};
};

#endif
