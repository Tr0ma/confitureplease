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
	class Gem
	{
	public:
		GemVO*	m_GemVO;
		Image*	m_Image;
	};


private:
	const float					CELL_SIZE;
	const float					GEM_SIZE;

	int							m_NumRows;
	int							m_NumCols;

	TextureAtlas*				m_Atlas;
	DisplayObjectContainer*		m_GridContainer;
	DisplayObjectContainer*		m_CandyContainer;

	vector<Gem*>				m_GemList;

public:
	static const char* ID;

public:
	GridView() : CELL_SIZE(100.0f), GEM_SIZE(90.0f), m_NumRows(9), m_NumCols(9) {}
	~GridView();

public:
	Gem& AddCell(int colId, int rowId, GemVO& gemVO);

protected:
	virtual void	CreateView() override;

};

#endif