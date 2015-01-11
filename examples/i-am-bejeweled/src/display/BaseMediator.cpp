#include "BaseMediator.h"
#include "AssetManager.h"
#include "Injector.h"
#include "BaseView.h"

void BaseMediator::OnInitialized()
{
	AssetManager* assetManager = GetInjector().GetInstanceById<AssetManager>(AssetManager::ID);
	BaseView& view = GetView<BaseView>();
	view.SetAssetManager(*assetManager);
	view.CreateView();
}