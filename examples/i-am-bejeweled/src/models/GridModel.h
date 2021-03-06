#ifndef _GRIDMODEL_H_
#define _GRIDMODEL_H_

#include "Pool.h"
#include "GemVO.h"

#include <vector>

using namespace std;

class PatternListVO;

class GridModel
{
public:
	static const char* ID;

private:
	int						m_NumCols;
	int						m_NumRows;
	vector<vector<GemVO*>*>	m_List;
	Pool<GemVO>				m_GemPool;

public:
	int			GetNumCols() const		{ return m_NumCols; }
	void		SetNumCols(int value)	{ m_NumCols = value; }

	int			GetNumRows() const		{ return m_NumRows; }
	void		SetNumRows(int value)	{ m_NumRows = value; }

public:
	GridModel() : m_NumCols(9), m_NumRows(9) {}
	~GridModel();

	GemVO&			AddGem(const char* textureId);
	GemVO&			AddGemAt(const char* textureId, const int colId, const int rowId);
	GemVO*			GetGemAt(const int colId, const int rowId) const;
	void			MoveGemAt(const int colId, const int rowId, GemVO& gemVO);
	void			MoveGemAt(const float x, const float y, GemVO& gemVO);
	void			RemoveGemAt(const int colId, const int rowId);
	void			GetPatternByGem(GemVO& gem, PatternListVO* result);

private:
	void			CheckHorizontal(GemVO& gem, PatternListVO* result);
	void			CheckVertical(GemVO& gem, PatternListVO* result);
};

#endif