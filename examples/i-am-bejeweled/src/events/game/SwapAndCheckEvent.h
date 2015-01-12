#ifndef _SWAPANDCHECKEVENT_H_
#define _SWAPANDCHECKEVENT_H_
#include <Event.h>

class Vec2d;
class GemVO;

class SwapAndCheckEvent : public Event
{
public:
	static const char* TYPE;

	GemVO&			m_GemVO;
	const Vec2d&	m_Direction;

public:
	explicit SwapAndCheckEvent(GemVO& gemVO, const Vec2d& direction) 
		: Event(TYPE), m_GemVO(gemVO), m_Direction(direction) {}

	~SwapAndCheckEvent() {}
};

#endif