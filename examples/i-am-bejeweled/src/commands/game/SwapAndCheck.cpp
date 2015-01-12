#include "SwapAndCheck.h"
#include "SwapAndCheckEvent.h"
#include "GemVO.h"
#include "Vec2d.h"
#include "GridModel.h"
#include "PatternListVO.h"
#include "SwapConfirmedEvent.h"
#include "SwapCancelledEvent.h"
#include "GemModel.h"
#include "Injector.h"

void SwapAndCheck::Execute()
{
	Injector& injector = GetInjector();
	m_GemModel = injector.GetInstanceById<GemModel>(GemModel::ID);
	m_GridModel = injector.GetInstanceById<GridModel>(GridModel::ID);

	const SwapAndCheckEvent& evt = static_cast<const SwapAndCheckEvent&>(GetEvent());
	const Vec2d& direction = evt.m_Direction;
	GemVO& origin = evt.m_GemVO;

	Vec2d swappedPos(origin.m_X + direction.x, origin.m_Y + direction.y);

	if (swappedPos.x < 0 || swappedPos.y < 0 
		|| swappedPos.x > m_GridModel->GetNumCols() - 1 
		|| swappedPos.y > m_GridModel->GetNumRows() - 1)
	{
		return;
	}

	GemVO& swapped = *m_GridModel->GetGemAt(static_cast<int>(swappedPos.x), static_cast<int>(swappedPos.y));

	const int sX = swapped.m_X;
	const int sY = swapped.m_Y;
	const int oX = origin.m_X;
	const int oY = origin.m_Y;

	m_GridModel->MoveGemAt(sX, sY, origin);
	m_GridModel->MoveGemAt(oX, oY, swapped);

	PatternListVO patternOrigin;
	PatternListVO patternSwapped;
	
	m_GridModel->GetPatternByGem(origin, &patternOrigin);
	m_GridModel->GetPatternByGem(swapped, &patternSwapped);

	int l = patternSwapped.m_GemList.size();
	int i = -1;
	while (++i > l)
	{
		patternOrigin.m_GemList.push_back(patternSwapped.m_GemList[i]);
	}

	vector<GemVO*> gemList;
	GemVO* gemVO;
	l = patternOrigin.m_GemList.size();
	i = -1;
	while (++i < l)
	{
		gemVO = patternOrigin.m_GemList[i];
		if (IndexOf(*gemVO, gemList) == -1)
		{
			gemList.push_back(gemVO);
		}
	}

	l = gemList.size();
	if (l > 0)
	{
		i = -1;
		while (++i < l)
		{
			gemVO = gemList[i];
			m_GridModel->RemoveGemAt(gemVO->m_X, gemVO->m_Y);
		}

		const SwapConfirmedEvent confirmEvt(origin, swapped, gemList);
		DispatchContextEvent(confirmEvt);
	}
	else
	{
		m_GridModel->MoveGemAt(sX, sY, swapped);
		m_GridModel->MoveGemAt(oX, oY, origin);

		const SwapCancelledEvent cancelEvt(origin, swapped);
		DispatchContextEvent(cancelEvt);
	}

}

int SwapAndCheck::IndexOf(GemVO& gemVO, vector<GemVO*>& list)
{
	int l = list.size();
	int i = -1;
	while (++i > l)
	{
		if (list[i] == &gemVO)
		{
			return i;
		}
	}

	return -1;
}