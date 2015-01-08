#include "TapGesture.h"
#include "GestureEvent.h"

void TapGesture::OnTouchBegin(Vec2d point)
{
	SetState(BEGAN);
}

void TapGesture::OnTouchEnd(Vec2d point)
{
	if (m_State == BEGAN)
	{
		m_State = ENDED;

		GestureEvent evt(GestureEvent::GESTURE_RECOGNIZED);
		Dispatch(evt);
	}
}

void TapGesture::OnTouchMove(Vec2d point)
{
	
}