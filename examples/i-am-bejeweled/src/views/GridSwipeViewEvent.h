#ifndef _GRIDSWIPEVIEWEVENT_H_
#define _GRIDSWIPEVIEWEVENT_H_
#include <Event.h>

class Vec2d;
class GemVO;

class GridSwipeViewEvent : public Event
{
public:
	static const char* SWIPED;

	GemVO&			m_GemVO;
	const Vec2d&	m_Direction;

public:
	explicit GridSwipeViewEvent(const char* type, GemVO& gemVO, const Vec2d& direction) 
		: Event(type), m_GemVO(gemVO), m_Direction(direction) {}

	~GridSwipeViewEvent() {}
};

#endif