#ifndef _INITIALIZEGRIDEVENT_H_
#define _INITIALIZEGRIDEVENT_H_
#include <Event.h>

class InitializeGridEvent : public Event
{
public:
	static const char* TYPE;

public:
	InitializeGridEvent() : Event(TYPE) {};
	~InitializeGridEvent() {};
};

#endif