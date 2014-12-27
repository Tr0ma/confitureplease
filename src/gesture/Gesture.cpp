#include "Gesture.h"

void TouchesManager::OnTouchBegin(int x, int y)
{
	
}

void TouchesManager::OnTouchEnd(int x, int y)
{
	
}

void TouchesManager::OnTouchMove(int x, int y)
{
	
}

GestureManager::GestureManager(InputAdapter& inputAdapter) : m_InputAdapater(inputAdapter)
{
	m_TouchesManager = new TouchesManager(*this);
}

GestureManager::~GestureManager()
{
	delete m_TouchesManager;
}

TapGesture& GestureManager::GetTapGesture(Display& target)
{
	
}