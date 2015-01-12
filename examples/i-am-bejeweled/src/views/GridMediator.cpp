#include "GridMediator.h"
#include "Injector.h"
#include "ViewEvent.h"
#include "GridSwipeViewEvent.h"
#include "SwapAndCheckEvent.h"
#include "SwapCancelledEvent.h"
#include "SwapConfirmedEvent.h"
#include "MoveDownUpdatedEvent.h"
#include "PatternsFoundEvent.h"
#include "MoveCompleteEvent.h"

GridMediator::~GridMediator()
{
}

void GridMediator::OnInitialized()
{
	BaseMediator::OnInitialized();

	m_GridView = &GetView<GridView>();
	m_GridModel = GetInjector().GetInstanceById<GridModel>(GridModel::ID);

	m_GridView->AddListener(ViewEvent::VIEW_SHOWN, &GridMediator::OnViewShown, *this);
	m_GridView->AddListener(GridSwipeViewEvent::SWIPED, &GridMediator::OnSwiped, *this);

	AddContextListener(SwapCancelledEvent::TYPE, &GridMediator::OnSwapCancelled, *this);
	AddContextListener(SwapConfirmedEvent::TYPE, &GridMediator::OnSwapConfirmed, *this);
	AddContextListener(MoveDownUpdatedEvent::TYPE, &GridMediator::OnFillUpdated, *this);
	AddContextListener(PatternsFoundEvent::TYPE, &GridMediator::OnPatternsFound, *this);
	AddContextListener(MoveCompleteEvent::TYPE, &GridMediator::OnMoveComplete, *this);
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

void GridMediator::OnSwapCancelled(const Event& evt)
{
	const SwapCancelledEvent& cancelEvt = static_cast<const SwapCancelledEvent&>(evt);
	m_GridView->SwapThenCancel(cancelEvt.m_GemA, cancelEvt.m_GemB);

	m_GridView->GetContainer().SetTouchable(true);
}

void GridMediator::OnSwapConfirmed(const Event& evt)
{
	const SwapConfirmedEvent& confirmEvt = static_cast<const SwapConfirmedEvent&>(evt);
	m_GridView->SwapThenDelete(confirmEvt.m_GemA, confirmEvt.m_GemB, confirmEvt.m_GemList);
}

void GridMediator::OnDeleteComplete(const Event& evt)
{
}

void GridMediator::OnFillUpdated(const Event& evt)
{
}

void GridMediator::OnPatternsFound(const Event& evt)
{
}

void GridMediator::OnMoveComplete(const Event& evt)
{
}