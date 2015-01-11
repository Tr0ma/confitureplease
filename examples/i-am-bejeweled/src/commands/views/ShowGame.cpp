#include "ShowGame.h"
#include "MediatorMap.h"
#include "GridView.h"
#include "Confiture.h"
#include "Injector.h"

void ShowGame::Execute()
{
	Confiture* confiture = GetInjector().GetInstanceById<Confiture>(Confiture::ID);
	GridView* view = GetMediatorMap().GetView<GridView>(GridView::ID);

	confiture->GetStage().AddChild(view->GetContainer());
	view->Show();
}