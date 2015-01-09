#include "GestureManager.h"
#include "Stage.h"
#include "TouchesManager.h"
#include <iostream>

using namespace std;

GestureManager::GestureManager(InputAdapter& inputAdapter, Stage& stage) : m_InputAdapater(inputAdapter), m_Stage(stage)
{
	m_TouchesManager = new TouchesManager(*this, m_Stage);
	inputAdapter.SetTouchesManager(*m_TouchesManager);
}

void GestureManager::OnTouchBegin(Touch& touch)
{
	cout << "touch begin" << endl;

	const unsigned short l = m_Items.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		GestureMapItem& item = *m_Items[i];
		Gesture& gesture = item.GetGesture();

		if (!gesture.GetEnabled()) continue;

		if (&gesture.GetTarget() == touch.GetTarget())
		{
			gesture.BeginTouch(touch.GetLocation());
		}
	}
}

void GestureManager::OnTouchEnd(Touch& touch)
{
	cout << "touch end" << endl;
	const unsigned short l = m_Items.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		GestureMapItem& item = *m_Items[i];
		Gesture& gesture = item.GetGesture();

		if (!gesture.GetEnabled()) continue;

		if (&gesture.GetTarget() == touch.GetTarget())
		{
			gesture.EndTouch(touch.GetLocation());
		}
	}
}

void GestureManager::OnTouchMove(Touch& touch)
{
	cout << "touch move" << endl;
	const unsigned short l = m_Items.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		GestureMapItem& item = *m_Items[i];
		Gesture& gesture = item.GetGesture();

		if (!gesture.GetEnabled()) continue;

		if (&gesture.GetTarget() == touch.GetTarget())
		{
			gesture.MoveTouch(touch.GetLocation());
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