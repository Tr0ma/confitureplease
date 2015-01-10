#include "ScreenManager.h"

void ScreenManager::OnNextScreen(Event& evt)
{
	m_Busy = false;

	ScreenManagerEvent managerEvt(ScreenManagerEvent::TRANSITION_COMPLETE);
	Dispatch(managerEvt);
}