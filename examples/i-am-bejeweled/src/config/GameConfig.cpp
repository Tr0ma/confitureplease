#include "GameConfig.h"
#include "DirectCommandMap.h"
#include "EventCommandMap.h"
#include "MediatorMap.h"
#include "Injector.h"

// Command
#include "StartupApplication.h"
#include "ShowStartMenu.h"
#include "ShowGame.h"

// Views
#include "StartMenuView.h"
#include "GridView.h"

// Mediators
#include "StartMenuMediator.h"
#include "GridMediator.h"

// Events
#include "ShowStartMenuEvent.h"
#include "ShowGameEvent.h"

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
	mediatorMap.Map(StartMenuView::ID, &GameConfig::GetStartMenuView, *this).To(&GameConfig::GetStartMenuMediator, *this);
	mediatorMap.Map(GridView::ID, &GameConfig::GetGridView, *this).To(&GameConfig::GetGridMediator, *this);

	EventCommandMap& eventCommandMap = GetEventCommandMap();
	eventCommandMap.Map(ShowStartMenuEvent::TYPE, &GameConfig::GetShowStartMenu, *this);
	eventCommandMap.Map(ShowGameEvent::TYPE, &GameConfig::GetShowGame, *this);
}

void GameConfig::Dispose()
{
	Injector& injector = GetInjector();
	delete injector.GetInstanceById<Confiture>(Confiture::ID);
	delete injector.GetInstanceById<AssetManager>(AssetManager::ID);
}

// Commands
Command& GameConfig::GetStartUpApplication() { return *(new StartupApplication()); }
Command& GameConfig::GetShowStartMenu() { return *(new ShowStartMenu()); }
Command& GameConfig::GetShowGame() { return *(new ShowGame()); };

// Views
View& GameConfig::GetStartMenuView() { return *(new StartMenuView()); }
View& GameConfig::GetGridView() { return *(new GridView()); }

// Mediators
Mediator& GameConfig::GetStartMenuMediator() { return *(new StartMenuMediator()); }
Mediator& GameConfig::GetGridMediator() { return *(new GridMediator()); }