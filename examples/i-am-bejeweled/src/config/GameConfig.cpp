#include "GameConfig.h"
#include "DirectCommandMap.h"
#include "Injector.h"
#include "StartupApplication.h"

#include "Rectangle.h"
#include "Confiture.h"
#include <Iw2D.h>

void GameConfig::Configure()
{
	Rectangle viewport = Rectangle(0, 0, Iw2DGetSurfaceWidth(),Iw2DGetSurfaceHeight());
	confiture = new Confiture(viewport);

	Injector& injector = GetInjector();
	injector.Map(confiture, Confiture::CONFITURE_ID);

	DirectCommandMap& directCommandMap = GetDirectCommandMap();
	GetDirectCommandMap().Map(&GameConfig::GetStartUpApplication, *this);
}

void GameConfig::Dispose()
{
	Injector& injector = GetInjector();
	Confiture* confiture = injector.GetInstanceById<Confiture>(Confiture::CONFITURE_ID);
	delete confiture;
}

Command& GameConfig::GetStartUpApplication() { return *(new StartupApplication()); };