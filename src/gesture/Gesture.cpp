#include "Gesture.h"
#include <iostream>

using namespace std;

const char* GestureEvent::GESTURE_RECOGNIZED = "GestureEvent_GESTURE_RECOGNIZED";

void Gesture::BeginTouch(Vec2d point)
{
	m_TouchCount++;

	OnTouchBegin(point);
}

void Gesture::EndTouch(Vec2d point)
{
	m_TouchCount--;

	OnTouchEnd(point);
}

void Gesture::MoveTouch(Vec2d point)
{
	OnTouchMove(point);
}

void Gesture::SetState(GestureState state)
{
	m_State = state;
}

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

GestureManager::GestureManager(InputAdapter& inputAdapter, Stage& stage) : m_InputAdapater(inputAdapter), m_Stage(stage)
{
	inputAdapter.SetGestureManager(*this);
}

void GestureManager::OnTouchBegin(Vec2d point)
{
	cout << "touch begin" << endl;

    DisplayObject* target = m_Stage.HitTest(point);

    if (!target || target == &m_Stage)
    {
        return;
    }

	const unsigned short l = m_Items.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		GestureMapItem& item = *m_Items[i];
		Gesture& gesture = item.GetGesture();

		if (!gesture.GetEnabled()) continue;

		if (&gesture.GetTarget() == target)
		{
			gesture.BeginTouch(point);
		}
	}
}

void GestureManager::OnTouchEnd(Vec2d point)
{
	cout << "touch end" << endl;
	const unsigned short l = m_Items.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		GestureMapItem& item = *m_Items[i];
		Gesture& gesture = item.GetGesture();

		if (!gesture.GetEnabled()) continue;

		if (gesture.GetTarget().HitTest(point))
		{
			gesture.EndTouch(point);
		}
	}
}

void GestureManager::OnTouchMove(Vec2d point)
{
	cout << "touch move" << endl;
	const unsigned short l = m_Items.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		GestureMapItem& item = *m_Items[i];
		Gesture& gesture = item.GetGesture();

		if (!gesture.GetEnabled()) continue;

		if (gesture.GetTarget().HitTest(point))
		{
			gesture.MoveTouch(point);
		}
	}
}

void GestureManager::Update(float deltaTime)
{
	m_InputAdapater.Update(deltaTime);
}

TapGesture& GestureManager::GetTapGesture(DisplayObject& target)
{
	return *(new TapGesture(target));
}