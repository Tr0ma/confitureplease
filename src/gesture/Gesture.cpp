#include "Gesture.h"
#include <iostream>

using namespace std;

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