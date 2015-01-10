#include "GameConfig.h"

#include "DirectCommandMap.h"

#include "StartupApplication.h"

void GameConfig::Configure()
{
	GetDirectCommandMap().Map(&GameConfig::GetStartUpApplication, *this);
}

Command& GameConfig::GetStartUpApplication() { return *(new StartupApplication()); };