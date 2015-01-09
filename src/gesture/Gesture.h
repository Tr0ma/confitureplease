#ifndef _GESTURE_H_
#define _GESTURE_H_

#include "EventDispatcher.h"
#include "DisplayObject.h"

class Gesture : public EventDispatcher
{
private:
	DisplayObject&	m_Target;
	bool			m_Enabled;

protected:
	int				m_TouchCount;

	enum GestureState
	{
		BEGAN,
		ENDED
	};

	GestureState	m_State;

public:
	DisplayObject&	GetTarget() { return m_Target; }

	bool		GetEnabled()			{ return m_Enabled; }
	void		SetEnabled(bool value)	{ m_Enabled = value; }

public:
	explicit Gesture(DisplayObject& target) : m_Target(target), m_TouchCount(0) {}
	virtual ~Gesture() {}

    bool isTrackingTouch(int touchId);

	void BeginTouch(Vec2d point);
	void EndTouch(Vec2d point);
	void MoveTouch(Vec2d point);

protected:
	void SetState(GestureState state);

	virtual void OnTouchBegin(Vec2d point) {}
	virtual void OnTouchEnd(Vec2d point) {}
	virtual void OnTouchMove(Vec2d point) {}
};

#endif