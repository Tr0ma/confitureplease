#ifndef _SHOWGAMEEVENT_H_
#define _SHOWGAMEEVENT_H_
#include <Event.h>

class ShowGameEvent : public Event
{
public:
	static const char* TYPE;

public:
	ShowGameEvent() : Event(TYPE) {};
	~ShowGameEvent() {};
};

#endif
