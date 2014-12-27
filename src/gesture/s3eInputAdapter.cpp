#include "s3eInputAdapter.h"

s3eInputAdapter::s3eInputAdapter()
{
	if (s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) != 0)
    {
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, nullptr);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, nullptr);
    }
    else
    {
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)TouchButtonCB, nullptr);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)TouchMotionCB, nullptr);
	}
}

void s3eInputAdapter::Update(float deltaTime = 0.0f)
{
	s3ePointerUpdate();
}

void s3eInputAdapter::TouchButtonCB(s3ePointerEvent* event)
{
	if (event->m_Pressed)
	{
		m_TouchesManager->OnTouchBegin(event->m_x, event->m_y);
	}
	else
	{
		m_TouchesManager->OnTouchEnd(event->m_x, event->m_y);
	}
}

void s3eInputAdapter::TouchMotionCB(s3ePointerMotionEvent* event)
{
	m_TouchesManager->OnTouchMove(event->m_x, event->m_y);
}

void s3eInputAdapter::MultiTouchButtonCB(s3ePointerTouchEvent* event)
{
	if (event->m_Pressed)
	{
		m_TouchesManager->OnTouchBegin(event->m_x, event->m_y);
	}
	else
	{
		m_TouchesManager->OnTouchEnd(event->m_x, event->m_y);
	}
}

void s3eInputAdapter::MultiTouchMotionCB(s3ePointerTouchMotionEvent* event)
{
	m_TouchesManager->OnTouchMove(event->m_x, event->m_y);
}

