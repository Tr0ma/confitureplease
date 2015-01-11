#include "ShowStartMenu.h"
#include "MediatorMap.h"
#include "StartMenuView.h"
#include "Confiture.h"
#include "Injector.h"

void ShowStartMenu::Execute()
{
	Confiture* confiture = GetInjector().GetInstanceById<Confiture>(Confiture::ID);
	StartMenuView* view = GetMediatorMap().GetView<StartMenuView>(StartMenuView::ID);

	confiture->GetStage().AddChild(view->GetContainer());
	view->Show();
}