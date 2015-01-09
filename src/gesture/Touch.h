#ifndef _TOUCH_H_
#define _TOUCH_H_

#include "DisplayObject.h"

class Touch
{
private:
	int				m_Id;
	DisplayObject*	m_Target;
	Vec2d			m_Location;
	Vec2d			m_PrevLocation;
	Vec2d			m_BeginLocation;
	long			m_Time;
	long			m_BeginTime;

public:
	int				GetId()								{ return m_Id; }
	void			SetId(int value)					{ m_Id = value; }

	DisplayObject*	GetTarget()							{ return m_Target; }
	void			SetTarget(DisplayObject* value)		{ m_Target = value; }

	Vec2d			GetLocation()						{ return m_Location; }
	Vec2d			GetPrevLocation()					{ return m_PrevLocation; }
	Vec2d			GetBeginLocation()					{ return m_BeginLocation; }

	long			GetTime()							{ return m_Time; }
	void			SetTime(long value)					{ m_Time = value; }

	long			GetBeginTime()						{ return m_BeginTime; }
	void			SetBeginTime(long value)			{ m_BeginTime = value; }

public:
	Touch() {}
	~Touch() {}

	void SetLocation(Vec2d& point, long time);
	bool UpdateLocation(Vec2d& point, long time);
};

#endif