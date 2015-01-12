#include "TouchesManager.h"
#include "Stage.h"
#include <time.h>

long	TouchesManager::timeHelper;

TouchesManager::~TouchesManager()
{
	int i = m_ActiveTouchesCount;
	while (--i >= 0)
	{
		delete m_TouchList[i];
	}

	m_TouchList.clear();
}

void TouchesManager::OnTouchBegin(int touchID, Vec2d& point)
{
	if (GetTouchByTouchID(touchID))
	{
		return;
	}

	Touch* touch = new Touch();
	touch->SetId(touchID);

	DisplayObject& target = *m_Stage.HitTest(point);
	touch->SetTarget(&target);

	timeHelper = time(nullptr);
	touch->SetLocation(point, timeHelper);

	m_TouchList.push_back(touch);
	m_ActiveTouchesCount++;

	m_GestureManager.OnTouchBegin(*touch);
}

void TouchesManager::OnTouchEnd(int touchID, Vec2d& point)
{
	int index = GetIndexByTouchID(touchID);
	if (index == -1) return;

	Touch* touch = m_TouchList[index];
	timeHelper = time(nullptr);
	touch->UpdateLocation(point, timeHelper);

	m_TouchList.erase(m_TouchList.begin() + index);
	m_ActiveTouchesCount--;

	m_GestureManager.OnTouchEnd(*touch);

	touch->SetTarget(nullptr);
}

void TouchesManager::OnTouchMove(int touchID, Vec2d& point)
{
	int index = GetIndexByTouchID(touchID);
	if (index == -1) return;

	Touch* touch = m_TouchList[index];
	timeHelper = time(nullptr);
	if (touch->UpdateLocation(point, timeHelper))
	{
		m_GestureManager.OnTouchMove(*touch);
	}
}

Touch* TouchesManager::GetTouchByTouchID(int touchID)
{
	const unsigned int l = m_TouchList.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		Touch& touch = *(m_TouchList[i]);
		if (touch.GetId() == touchID)
		{
			return &(touch);
		}
	}

	return nullptr;
}

int TouchesManager::GetIndexByTouchID(int touchID)
{
	const unsigned int l = m_TouchList.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		Touch& touch = *(m_TouchList[i]);
		if (touch.GetId() == touchID)
		{
			return i;
		}
	}

	return -1;
}