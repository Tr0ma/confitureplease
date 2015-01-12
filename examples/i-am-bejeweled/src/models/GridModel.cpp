#include "GridModel.h"
#include "GemVO.h"
#include "PatternListVO.h"

const char* GridModel::ID = "GridModel_ID";

GridModel::~GridModel()
{
	vector<GemVO*>* row;
	GemVO* gemVO;
	int i;
	int j = -1;

	while (++j < m_NumRows)
	{
		row = m_List[j];
		i = -1;

		while (++i < m_NumCols)
		{
			gemVO = (*row)[i];
			delete gemVO;
		}

		row->clear();
		delete row;
	}
	
	m_List.clear();
}

GemVO& GridModel::AddGem(const char* textureId)
{
	vector<GemVO*>* row;
	const int l = m_List.size();

	if (l - 1 < 0)
	{
		row = new vector<GemVO*>();
		m_List.push_back(row);
	}
	else
	{
		row = m_List[l - 1];
		const int rowSize = row->size();
		if (rowSize >= m_NumCols)
		{
			row = new vector<GemVO*>();
			m_List.push_back(row);
		}
	}

	GemVO* gemVO = new GemVO();
	gemVO->m_Type = textureId;
	gemVO->m_X = row->size();
	gemVO->m_Y = m_List.size() - 1;

	row->push_back(gemVO);
	
	return *gemVO;
}

GemVO& GridModel::AddGemAt(const char* textureId, const int colId, const int rowId)
{
	GemVO* gemVO = new GemVO();
	gemVO->m_Type = textureId;
	gemVO->m_X = colId;
	gemVO->m_Y = rowId;

	(*m_List[rowId])[colId] = gemVO;

	return *gemVO;
}

GemVO& GridModel::GetGemAt(const int colId, const int rowId) const
{
	return *(*m_List[rowId])[colId];
}

void GridModel::MoveGemAt(const int colId, const int rowId, GemVO& gemVO)
{
	(*m_List[rowId])[colId] = &gemVO;
	gemVO.m_X = colId;
	gemVO.m_Y = rowId;
}

void GridModel::RemoveGemAt(const int colId, const int rowId)
{
	delete (*m_List[rowId])[colId];
}

void GridModel::GetPatternByGem(GemVO& gemVO, const char* patternType, PatternListVO* result)
{
	PatternListVO* horizontal = new PatternListVO();
	PatternListVO* vertical = new PatternListVO();

	CheckHorizontal(gemVO, patternType, horizontal);
	CheckHorizontal(gemVO, patternType, vertical);

	result->m_GemList.insert(result->m_GemList.begin() + result->m_GemList.size(), horizontal->m_GemList.begin(), horizontal->m_GemList.end());
	result->m_GemList.insert(result->m_GemList.begin() + result->m_GemList.size(), vertical->m_GemList.begin(), vertical->m_GemList.end());
}

void GridModel::CheckHorizontal(GemVO& gemVO, const char* patternType, PatternListVO* result)
{
	vector<GemVO*>* gemList = &result->m_GemList;
	gemList->clear();

	gemList->push_back(&gemVO);
	int i = gemVO.m_X;
	int rowId = gemVO.m_Y;
	GemVO* gemTarget;

	while (--i > 0)
	{
		gemTarget = &GetGemAt(i, rowId);
		if (gemTarget->m_Type != gemVO.m_Type)
		{
			break;
		}

		gemList->push_back(gemTarget);
	}

	i = gemVO.m_X;
	int numCols = GetNumCols();
	while (++i <= numCols - 1)
	{
		gemTarget = &GetGemAt(i, rowId);
		if (gemTarget->m_Type != gemVO.m_Type)
		{
			break;
		}

		gemList->push_back(gemTarget);
	}

	if (gemList->size() < 3)
	{
		gemList->clear();
	}
}

void GridModel::CheckVertical(GemVO& gemVO, const char* patternType, PatternListVO* result)
{
	vector<GemVO*>* gemList = &result->m_GemList;
	gemList->clear();

	gemList->push_back(&gemVO);
	int j = gemVO.m_Y;
	int colId = gemVO.m_X;
	GemVO* gemTarget;

	while (--j > 0)
	{
		gemTarget = &GetGemAt(colId, j);
		if (gemTarget->m_Type != gemVO.m_Type)
		{
			break;
		}

		gemList->push_back(gemTarget);
	}

	j = gemVO.m_X;
	int numRows = GetNumRows();
	while (++j <= numRows - 1)
	{
		gemTarget = &GetGemAt(colId, j);
		if (gemTarget->m_Type != gemVO.m_Type)
		{
			break;
		}

		gemList->push_back(gemTarget);
	}

	if (gemList->size() < 3)
	{
		gemList->clear();
	}
}