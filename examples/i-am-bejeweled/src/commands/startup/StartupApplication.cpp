#include "StartupApplication.h"
#include "ShowStartMenuEvent.h"
#include "Injector.h"
#include "AssetManager.h"
#include "AtlasTypes.h"
#include "InitializeGridEvent.h"

void StartupApplication::Execute()
{
	AssetManager* assetManager = GetInjector().GetInstanceById<AssetManager>(AssetManager::ID);
	assetManager->AddAtlas(AtlasTypes::MY_ATLAS, "atlas/my-atlas.png", "atlas/my-atlas.json");

	/*const ShowStartMenuEvent evt;
	GetDispatcher().Dispatch(evt);*/

	const InitializeGridEvent evt;
	GetDispatcher().Dispatch(evt);


}