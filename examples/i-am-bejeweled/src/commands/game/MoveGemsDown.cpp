#include "MoveGemsDown.h"
#include "GemModel.h"
#include "GridModel.h"
#include "Injector.h"
#include "MoveDownUpdatedEvent.h"
#include <Vec2d.h>
#include <cmath>

void MoveGemsDown::Execute()
{
	Injector& injector = GetInjector();
	m_GemModel = injector.GetInstanceById<GemModel>(GemModel::ID);
	m_GridModel = injector.GetInstanceById<GridModel>(GridModel::ID);

	const int numRows = m_GridModel->GetNumRows();
	const int numCols = m_GridModel->GetNumCols();

	Vec2d moveDownPos;
	GemVO* gemVO = nullptr;
	vector<GemVO*> moveDownList;

	bool foundPos;
	int i = -1;
	int j;
	while (++i < numCols)
	{
		j = numRows;
		foundPos = false;

		while (--j >= 0)
		{
			gemVO = m_GridModel->GetGemAt(i, j);
			if (!foundPos)
			{
				if (!gemVO)
				{
					moveDownPos.Set(i, j);
				}
			}
			else
			{
				if (gemVO)
				{
					m_GridModel->MoveGemAt(moveDownPos.x, moveDownPos.y, *gemVO);
					m_GridModel->RemoveGemAt(i, j);

					moveDownPos.y -= 1;
					moveDownList.push_back(gemVO);
				}
			}
		}

		j = -1;
		const vector<const char*>& gemList = *m_GemModel->GetList();
		const int numGemTypes = gemList.size();
		int selectedId;
		const char* selectedTexture = nullptr;
		double rnd;
		vector<GemVO*> newGemsList;
		
		while (++j < numRows)
		{
			i = -1;
			while (++i < numCols)
			{
				if (!m_GridModel->GetGemAt(i, j))
				{
					rnd = static_cast<double>(rand()) / RAND_MAX;
					selectedId = static_cast<int>(floor(rnd * static_cast<float>(numGemTypes)));
					selectedTexture = gemList[selectedId];

					gemVO = &m_GridModel->AddGemAt(selectedTexture, i, j);
					newGemsList.push_back(gemVO);
				}
			}
		}

		const MoveDownUpdatedEvent evt(moveDownList, newGemsList);
		GetDispatcher().Dispatch(evt);
	}

}