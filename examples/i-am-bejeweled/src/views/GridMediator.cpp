#include "GridMediator.h"
#include "Injector.h"
#include "ViewEvent.h"
#include "GridSwipeViewEvent.h"
#include "SwapAndCheckEvent.h"

void GridMediator::OnInitialized()
{
	BaseMediator::OnInitialized();

	m_GridView = &GetView<GridView>();
	m_GridModel = GetInjector().GetInstanceById<GridModel>(GridModel::ID);

	m_GridView->AddListener(ViewEvent::VIEW_SHOWN, &GridMediator::OnViewShown, *this);
	m_GridView->AddListener(GridSwipeViewEvent::SWIPED, &GridMediator::OnSwiped, *this);
}

void GridMediator::InitializeGrid()
{
	int numRows = m_GridModel->GetNumRows();
	int numCols = m_GridModel->GetNumCols();
	int j = -1;
	int i;

	while (++j < numRows)
	{
		i = -1;
		while (++i < numCols)
		{
			m_GridView->AddCell(i, j, m_GridModel->GetGemAt(i, j));			
		}
	}
}

void GridMediator::OnViewShown(const Event& evt)
{
	m_GridView->RemoveListener(ViewEvent::VIEW_SHOWN, &GridMediator::OnViewShown, *this);

	InitializeGrid();
}

void GridMediator::OnSwiped(const Event& evt)
{
	const GridSwipeViewEvent& viewEvt = static_cast<const GridSwipeViewEvent&>(evt);
	m_GridView->GetContainer().SetTouchable(false);

	const SwapAndCheckEvent ctxEvt(viewEvt.m_GemVO, viewEvt.m_Direction);
	DispatchContextEvent(ctxEvt);
}