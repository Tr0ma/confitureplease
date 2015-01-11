#include "InitializeGrid.h"
#include "Injector.h"
#include "GridModel.h"
#include "GemModel.h"
#include "TextureTypes.h"
#include "GemVO.h"
#include <cmath>

void InitializeGrid::Execute()
{
	Injector& injector = GetInjector();
	m_GemModel = injector.GetInstanceById<GemModel>(GemModel::ID);
	m_GridModel = injector.GetInstanceById<GridModel>(GridModel::ID);

	m_GemModel->Register(TextureTypes::BLUE);
	m_GemModel->Register(TextureTypes::YELLOW);
	m_GemModel->Register(TextureTypes::BLUE);
	m_GemModel->Register(TextureTypes::GREEN);
	m_GemModel->Register(TextureTypes::PURPLE);

	int j = -1;
	int i;
	int selectedId;
	const char* selectedTexture = nullptr;
	bool validated;
	vector<const char*> gemTypeList;
	int numRows = m_GridModel->GetNumRows();
	int numCols = m_GridModel->GetNumCols();

	while (++j < numRows)
	{
		i = -1;
		while (++i < numCols)
		{
			validated = false;
			m_GemModel->GetListCopy(gemTypeList);

			/*while (!validated)
			{
				selectedId = static_cast<int>(floor(random() * static_cast<float>(gemTypeList.size())));
				selectedTexture = gemTypeList[i];

				if (IsHorizontalValid(i, j, selectedTexture) && IsVerticalValid(i, j, selectedTexture))
				{
					validated = true;
				}
			}*/

			/**** TMP ****/
			selectedId = static_cast<int>(floor(random() * static_cast<float>(gemTypeList.size())));
			selectedTexture = gemTypeList[i];
			/************/

			m_GridModel->AddGem(selectedTexture);
		}
	}
}

bool InitializeGrid::IsHorizontalValid(const int colId, const int rowId, const char* selection)
{
	if (colId <= 1)
	{
		return true;
	}

	const char* type;
	int i = colId - 1;
	GemVO* gemVO;

	while (i >= 0 && (colId -i) <= 2)
	{
		gemVO = &m_GridModel->GetGemAt(i, rowId);
		type = gemVO->m_Type;
		if (type != selection)
		{
			return true;
		}

		--i;
	}

	return false;
}

bool InitializeGrid::IsVerticalValid(const int colId, const int rowId, const char* selection)
{
	if (rowId <= 1)
	{
		return true;
	}

	const char* type;
	int j = rowId - 1;
	GemVO* gemVO;

	while (j >= 0 && (rowId - j) <= 2)
	{
		gemVO = &m_GridModel->GetGemAt(colId, j);
		type = gemVO->m_Type;
		if (type != selection)
		{
			return true;
		}

		--j;
	}

	return false;
}