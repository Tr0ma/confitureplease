#ifndef _TWEENEVENT_H_
#define _TWEENEVENT_H_

#include "Event.h"

class Tween;

class TweenEvent : public Event
{
public:
	static const char* START;
	static const char* UPDATE;
	static const char* COMPLETE;

private:
	Tween& m_Tween;

public:
	Tween&	GetTween() const { return m_Tween; }

public:
	explicit TweenEvent(const char* type, Tween& tween) 
		: Event(type), m_Tween(tween) {}

	virtual ~TweenEvent() {}
};

#endif
