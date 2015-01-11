#include "GridMediator.h"
#include "Injector.h"
#include "ViewEvent.h"

void GridMediator::OnInitialized()
{
	BaseMediator::OnInitialized();

	m_GridView = &GetView<GridView>();
	m_GridModel = GetInjector().GetInstanceById<GridModel>(GridModel::ID);

	m_GridView->AddListener(ViewEvent::VIEW_SHOWN, &GridMediator::OnViewShown, *this);
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