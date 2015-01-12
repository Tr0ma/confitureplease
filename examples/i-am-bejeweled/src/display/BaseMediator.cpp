#include "BaseMediator.h"
#include "AssetManager.h"
#include "Injector.h"
#include "BaseView.h"

void BaseMediator::OnInitialized()
{
	AssetManager* assetManager = GetInjector().GetInstanceById<AssetManager>(AssetManager::ID);
	GestureManager* gestureManager = GetInjector().GetInstanceById<GestureManager>(GestureManager::ID);
	TweenManager* tweenManager = GetInjector().GetInstanceById<TweenManager>(TweenManager::ID);

	BaseView& view = GetView<BaseView>();
	view.SetAssetManager(*assetManager);
	view.SetGestureManager(*gestureManager);
	view.SetTweenManager(*tweenManager);
}