#include "GameConfig.h"
#include "DirectCommandMap.h"
#include "EventCommandMap.h"
#include "MediatorMap.h"
#include "Injector.h"

// Command
#include "StartupApplication.h"
#include "ShowStartMenu.h"
#include "ShowGame.h"
#include "InitializeGrid.h"
#include "SwapAndCheck.h"
#include "MoveGemsDown.h"
#include "CheckPattern.h"

// Views
#include "StartMenuView.h"
#include "GridView.h"

// Mediators
#include "StartMenuMediator.h"
#include "GridMediator.h"

// Events
#include "ShowStartMenuEvent.h"
#include "ShowGameEvent.h"
#include "InitializeGridEvent.h"
#include "SwapAndCheckEvent.h"
#include "CheckPatternEvent.h"
#include "MoveGemsDownEvent.h"

// Models
#include "GridModel.h"
#include "GemModel.h"

#include "Rectangle.h"
#include "Confiture.h"
#include "AssetManager.h"
#include "s3eInputAdapter.h"
#include "TweenManager.h"

#include <Iw2D.h>


void GameConfig::Configure()
{
	Injector& injector = GetInjector();
	Rectangle viewport = Rectangle(0, 0, Iw2DGetSurfaceWidth(),Iw2DGetSurfaceHeight());
	Confiture* confiture = new Confiture(viewport);
	GetContext().AddToRenderer(*confiture);

	s3eInputAdapter* inputAdapter = new s3eInputAdapter();
	GestureManager* gestureManager = new GestureManager(*inputAdapter, confiture->GetStage());
	GetContext().AddToUpdate(*gestureManager);

	TweenManager* tweenManager = new TweenManager();
	GetContext().AddToUpdate(*tweenManager);
	
	injector.Map(confiture, Confiture::ID);
	injector.Map(gestureManager, GestureManager::ID);
	injector.Map(tweenManager, TweenManager::ID);
	injector.Map(new AssetManager(), AssetManager::ID);
	injector.Map(new GridModel(), GridModel::ID);
	injector.Map(new GemModel(), GemModel::ID);

	DirectCommandMap& directCommandMap = GetDirectCommandMap();
	directCommandMap.Map(&GameConfig::GetStartUpApplication, *this);

	MediatorMap& mediatorMap = GetMediatorMap();
	mediatorMap.Map(StartMenuView::ID, &GameConfig::GetStartMenuView, *this).To(&GameConfig::GetStartMenuMediator, *this);
	mediatorMap.Map(GridView::ID, &GameConfig::GetGridView, *this).To(&GameConfig::GetGridMediator, *this);

	EventCommandMap& eventCommandMap = GetEventCommandMap();
	eventCommandMap.Map(ShowStartMenuEvent::TYPE, &GameConfig::GetShowStartMenu, *this);
	eventCommandMap.Map(ShowGameEvent::TYPE, &GameConfig::GetShowGame, *this);

	eventCommandMap.Map(InitializeGridEvent::TYPE, &GameConfig::GetInitializeGrid, *this);
	eventCommandMap.Map(SwapAndCheckEvent::TYPE, &GameConfig::GetSwapAndCheck, *this);
	eventCommandMap.Map(MoveGemsDownEvent::TYPE, &GameConfig::GetMoveGemsDown, *this);
	eventCommandMap.Map(CheckPatternEvent::TYPE, &GameConfig::GetCheckPatterns, *this);
}

void GameConfig::Dispose()
{
	Injector& injector = GetInjector();

	Confiture* confiture = injector.GetInstanceById<Confiture>(Confiture::ID);
	AssetManager* assetMnager = injector.GetInstanceById<AssetManager>(AssetManager::ID);
	GridModel* gridModel = injector.GetInstanceById<GridModel>(GridModel::ID);
	GemModel* gemModel = injector.GetInstanceById<GemModel>(GemModel::ID);
	GestureManager* gestureManager = injector.GetInstanceById<GestureManager>(GestureManager::ID);
	TweenManager* tweenManager = GetInjector().GetInstanceById<TweenManager>(TweenManager::ID);

	injector.UnMap(Confiture::ID);
	injector.UnMap(AssetManager::ID);
	injector.UnMap(GridModel::ID);
	injector.UnMap(GemModel::ID);
	injector.UnMap(GestureManager::ID);
	injector.UnMap(TweenManager::ID);

	delete confiture;
	delete assetMnager;
	delete gridModel;
	delete gemModel;
	delete &gestureManager->GetInputAdapter();
	delete gestureManager;
	delete tweenManager;
}

// Commands
Command& GameConfig::GetStartUpApplication() { return *(new StartupApplication()); }
Command& GameConfig::GetShowStartMenu() { return *(new ShowStartMenu()); }
Command& GameConfig::GetShowGame() { return *(new ShowGame()); };
Command& GameConfig::GetInitializeGrid() { return *(new InitializeGrid()); };
Command& GameConfig::GetSwapAndCheck() { return *(new SwapAndCheck()); }
Command& GameConfig::GetMoveGemsDown() { return *(new MoveGemsDown()); }
Command& GameConfig::GetCheckPatterns() { return *(new CheckPattern()); }

// Views
View& GameConfig::GetStartMenuView() { return *(new StartMenuView()); }
View& GameConfig::GetGridView() { return *(new GridView()); }

// Mediators
Mediator& GameConfig::GetStartMenuMediator() { return *(new StartMenuMediator()); }
Mediator& GameConfig::GetGridMediator() { return *(new GridMediator()); }