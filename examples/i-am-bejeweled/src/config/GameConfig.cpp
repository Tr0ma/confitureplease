#include "GameConfig.h"
#include "DirectCommandMap.h"
#include "EventCommandMap.h"
#include "MediatorMap.h"
#include "Injector.h"

// Command
#include "StartupApplication.h"
#include "ShowStartMenu.h"

// Views
#include "StartMenuView.h"

// Mediators
#include "StartMenuMediator.h"

// Events
#include "ShowStartMenuEvent.h"

#include "Rectangle.h"
#include "Confiture.h"
#include "AssetManager.h"
#include <Iw2D.h>


void GameConfig::Configure()
{
	Injector& injector = GetInjector();
	Rectangle viewport = Rectangle(0, 0, Iw2DGetSurfaceWidth(),Iw2DGetSurfaceHeight());
	Confiture* confiture = new Confiture(viewport);
	GetContext().AddToRenderer(*confiture);

	AssetManager* assetManager = new AssetManager();
	
	injector.Map(confiture, Confiture::ID);
	injector.Map(assetManager, AssetManager::ID);

	DirectCommandMap& directCommandMap = GetDirectCommandMap();
	directCommandMap.Map(&GameConfig::GetStartUpApplication, *this);

	MediatorMap& mediatorMap = GetMediatorMap();
	mediatorMap.Map(StartMenuView::STARTMENU_VIEW, &GameConfig::GetStartMenuView, *this).To(&GameConfig::GetStartMenuMediator, *this);

	EventCommandMap& eventCommandMap = GetEventCommandMap();
	eventCommandMap.Map(ShowStartMenuEvent::TYPE, &GameConfig::GetShowStartMenu, *this);
}

void GameConfig::Dispose()
{
	Injector& injector = GetInjector();
	delete injector.GetInstanceById<Confiture>(Confiture::ID);
	delete injector.GetInstanceById<AssetManager>(AssetManager::ID);
}

// Commands
Command& GameConfig::GetStartUpApplication() { return *(new StartupApplication()); }
Command& GameConfig::GetShowStartMenu() { return *(new ShowStartMenu()); };

// Views
View& GameConfig::GetStartMenuView() { return *(new StartMenuView()); }

// Mediators
Mediator& GameConfig::GetStartMenuMediator() { return *(new StartMenuMediator()); }