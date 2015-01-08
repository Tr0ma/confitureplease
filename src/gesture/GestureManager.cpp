#include "GestureManager.h"
#include "Stage.h"
#include <iostream>

using namespace std;

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