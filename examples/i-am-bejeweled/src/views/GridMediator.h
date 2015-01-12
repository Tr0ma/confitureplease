#ifndef _GRIDMEDIATOR_H_
#define _GRIDMEDIATOR_H_

#include "BaseMediator.h"
#include "GridView.h"
#include "GridModel.h"

class GridMediator : public BaseMediator
{
private:
	GridView*	m_GridView;
	GridModel*	m_GridModel;

public:
	GridMediator() {}
	~GridMediator() {}

private:
	void OnInitialized() override;
	void InitializeGrid();
	void OnViewShown(const Event& evt);
	void OnSwiped(const Event& evt);
};

#endif