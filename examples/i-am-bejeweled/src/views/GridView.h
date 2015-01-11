#ifndef _GRIDVIEW_H_
#define _GRIDVIEW_H_

#include "BaseView.h"
#include "Image.h"
#include "GemVO.h"
#include <vector>

using namespace std;

class GridView : public BaseView
{
private:
	const float					CELL_SIZE;

	int							m_NumRows;
	int							m_NumCols;

	TextureAtlas*				m_Atlas;
	DisplayObjectContainer*		m_GridContainer;
	DisplayObjectContainer*		m_CandyContainer;


public:
	static const char* ID;

public:
	GridView() : CELL_SIZE(100.0f), m_NumRows(9), m_NumCols(9) {}
	~GridView();

public:
	void AddCell(int colId, int rowId, GemVO& gemVO);

protected:
	virtual void	CreateView() override;

};

#endif