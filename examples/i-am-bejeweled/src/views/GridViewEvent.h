#ifndef _GRIDVIEWEVENT_H_
#define _GRIDVIEWEVENT_H_
#include <Event.h>

class GridViewEvent : public Event
{
public:
	static const char* DELETE_COMPLETE;
	static const char* MOVE_DOWN_COMPLETE;
	static const char* SWAP_COMPLETE;
	static const char* CANCEL_COMPLETE;

public:
	explicit GridViewEvent(const char* type) : Event(type) {}
	~GridViewEvent() {}
};

#endif