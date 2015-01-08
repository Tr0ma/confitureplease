#include "s3eInputAdapter.h"
#include <iostream>

using namespace std;

s3eInputAdapter::s3eInputAdapter()
{
	if (s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) != 0)
    {
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, this);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, this);
    }
    else
    {
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)TouchButtonCB, this);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)TouchMotionCB, this);
	}
}

void s3eInputAdapter::Update(float deltaTime)
{
	s3ePointerUpdate();
}

void s3eInputAdapter::TouchButtonCB(s3ePointerEvent* event, void* data)
{
	s3eInputAdapter* adapter = static_cast<s3eInputAdapter*>(data);

	if (event->m_Pressed)
	{
        adapter->GetGestureManager().OnTouchBegin(Vec2d(event->m_x, event->m_y));
	}
	else
	{
		adapter->GetGestureManager().OnTouchEnd(Vec2d(event->m_x, event->m_y));
	}
}

void s3eInputAdapter::TouchMotionCB(s3ePointerMotionEvent* event, void* data)
{
	s3eInputAdapter* adapter = static_cast<s3eInputAdapter*>(data);

	adapter->GetGestureManager().OnTouchMove(Vec2d(event->m_x, event->m_y));
}

void s3eInputAdapter::MultiTouchButtonCB(s3ePointerTouchEvent* event, void* data)
{
	s3eInputAdapter* adapter = static_cast<s3eInputAdapter*>(data);

	if (event->m_Pressed)
	{
		adapter->GetGestureManager().OnTouchBegin(Vec2d(event->m_x, event->m_y));
	}
	else
	{
		adapter->GetGestureManager().OnTouchEnd(Vec2d(event->m_x, event->m_y));
	}
}

void s3eInputAdapter::MultiTouchMotionCB(s3ePointerTouchMotionEvent* event, void* data)
{
	s3eInputAdapter* adapter = static_cast<s3eInputAdapter*>(data);

	adapter->GetGestureManager().OnTouchMove(Vec2d(event->m_x, event->m_y));
}

