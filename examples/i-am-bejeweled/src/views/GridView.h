#ifndef _GRIDVIEW_H_
#define _GRIDVIEW_H_

#include "BaseView.h"
#include "Image.h"
#include "GemVO.h"
#include "SwipeGesture.h"
#include <vector>

using namespace std;



class GridView : public BaseView
{
private:
	class Gem
	{
	public:
		GemVO*			m_GemVO;
		Image*			m_Image;
		SwipeGesture*	m_Gesture;

	public:
		Gem() : m_GemVO(nullptr), m_Image(nullptr){}
	};


private:
	const float					CELL_SIZE;
	const float					GEM_SIZE;

	int							m_NumRows;
	int							m_NumCols;

	TextureAtlas*				m_Atlas;
	DisplayObjectContainer*		m_GridContainer;
	DisplayObjectContainer*		m_CandyContainer;

	Pool<Gem>					m_GemPool;
	vector<Gem*>				m_GemList;
	vector<Gem*>				m_DeleteList;

public:
	static const char* ID;

public:
	GridView() : CELL_SIZE(100.0f), GEM_SIZE(90.0f), m_NumRows(9), m_NumCols(9) {}
	~GridView();

public:
	Gem&			AddCell(int colId, int rowId, GemVO& gemVO);
	void			SwapThenCancel(GemVO& gemA, GemVO& gemB);
	void			SwapThenDelete(GemVO& gemA, GemVO& gemB, vector<GemVO*>& list);
	void			MoveDown(vector<GemVO*>& moveDownList, vector<GemVO*>& newGemsList);
	void			DeleteGems(vector<GemVO*>& list);

protected:
	virtual void	CreateView() override;

private:
	void			OnSwipe(const Event& evt);
	GemVO*			GetGemVOByTarget(const DisplayObject& target) const;
	Gem*			GetGemByGemVO(const GemVO& gemVO) const;
	DisplayObject*	GetTargetbyGemVO(const GemVO& gemVO) const;
	int				GetGemIndex(const Gem& gem);

	void			PlaySwap(DisplayObject& targetA, DisplayObject& targetB, float duration = 0.1f);
	void			CancelSwap(DisplayObject& targetA, DisplayObject& targetB, float duration, float delay);
	void			PlayDelete(vector<GemVO*>& list, float duration, float delay);

	void			OnDeleteComplete(const Event& evt);

};

#endif