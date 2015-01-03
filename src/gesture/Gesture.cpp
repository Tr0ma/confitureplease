#include "Gesture.h"
#include <iostream>

using namespace std;

const char* GestureEvent::GESTURE_RECOGNIZED = "GestureEvent_GESTURE_RECOGNIZED";

void Gesture::BeginTouch(int x, int y)
{
	m_TouchCount++;

	OnTouchBegin(x, y);
}

void Gesture::EndTouch(int x, int y)
{
	m_TouchCount--;

	OnTouchEnd(x, y);
}

void Gesture::MoveTouch(int x, int y)
{
	OnTouchMove(x, y);
}

void Gesture::SetState(GestureState state)
{
	m_State = state;
}

void TapGesture::OnTouchBegin(int x, int y)
{
	SetState(BEGAN);
}

void TapGesture::OnTouchEnd(int x, int y)
{
	if (m_State == BEGAN)
	{
		m_State = ENDED;

		GestureEvent evt(GestureEvent::GESTURE_RECOGNIZED);
		Dispatch(evt);
	}
}

void TapGesture::OnTouchMove(int x, int y)
{
	
}

GestureManager::GestureManager(InputAdapter& inputAdapter) : m_InputAdapater(inputAdapter)
{
	inputAdapter.SetGestureManager(*this);
};

void GestureManager::OnTouchBegin(int x, int y)
{
	cout << "touch begin" << endl;

	const unsigned short l = m_Items.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		GestureMapItem& item = *m_Items[i];
		Gesture& gesture = item.GetGesture();

		if (!gesture.GetEnabled()) continue;

		if (gesture.GetTarget().HitTest(x, y))
		{
			gesture.BeginTouch(x, y);
		}
	}
}

void GestureManager::OnTouchEnd(int x, int y)
{
	cout << "touch end" << endl;
	const unsigned short l = m_Items.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		GestureMapItem& item = *m_Items[i];
		Gesture& gesture = item.GetGesture();

		if (!gesture.GetEnabled()) continue;

		if (gesture.GetTarget().HitTest(x, y))
		{
			gesture.EndTouch(x, y);
		}
	}
}

void GestureManager::OnTouchMove(int x, int y)
{
	cout << "touch move" << endl;
	const unsigned short l = m_Items.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		GestureMapItem& item = *m_Items[i];
		Gesture& gesture = item.GetGesture();

		if (!gesture.GetEnabled()) continue;

		if (gesture.GetTarget().HitTest(x, y))
		{
			gesture.MoveTouch(x, y);
		}
	}
}

void GestureManager::Update(float deltaTime)
{
	m_InputAdapater.Update(deltaTime);
}

TapGesture& GestureManager::GetTapGesture(Container& target)
{
	return *(new TapGesture(target));
}