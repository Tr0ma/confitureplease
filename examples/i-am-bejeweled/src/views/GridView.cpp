#include "GridView.h"
#include "AtlasTypes.h"
#include "TextureTypes.h"
#include "Stage.h"

#include <iostream>

using namespace std;

const char* GridView::ID = "GridView_ID";

GridView::~GridView()
{
	DisplayObject* child;
	int j = m_GridContainer->GetNumChildren();
	while (--j >= 0)
	{
		child = &m_GridContainer->RemoveChildAt(j);
		delete child;
	}

	Gem* gem;
	j = m_GemList.size();
	while (--j >= 0)
	{
		gem = m_GemList[j];
		m_CandyContainer->RemoveChild(*gem->m_Image);
		delete gem->m_Image;
		delete gem;
	}

	m_GemList.clear();

	DisplayObjectContainer& container = GetContainer();
	container.RemoveChild(*m_GridContainer);
	container.RemoveChild(*m_CandyContainer);

	delete m_GridContainer;
	delete m_CandyContainer;

	// should main container be removed here?
	container.GetParent()->RemoveChild(container);
}

GridView::Gem& GridView::AddCell(int colId, int rowId, GemVO& gemVO)
{
	cout << gemVO.m_Type << " [x:" << gemVO.m_X << " , y:" << gemVO.m_Y << "]" << endl;

	Gem* gem = new Gem();
	m_GemList.push_back(gem);

	Image* image = new Image(*m_Atlas->GetTexture(gemVO.m_Type));
	image->SetWidth(GEM_SIZE);
	image->SetScaleY(image->GetScaleX());

	if (image->GetHeight() > GEM_SIZE)
	{
		image->SetHeight(GEM_SIZE);
		image->SetScaleX(image->GetScaleY());
	}

	image->SetX(colId * CELL_SIZE + CELL_SIZE / 2 - image->GetWidth() / 2);
	image->SetY(rowId * CELL_SIZE + CELL_SIZE / 2 - image->GetHeight() / 2);

	gem->m_Image = image;
	gem->m_GemVO = &gemVO;

	m_CandyContainer->AddChild(*image);

	return *gem;
}

void GridView::CreateView()
{
	m_Atlas = GetAssetManager().GetTextureAtlas(AtlasTypes::MY_ATLAS);

	DisplayObjectContainer& container = GetContainer();

	m_GridContainer = new DisplayObjectContainer();
	container.AddChild(*m_GridContainer);

	m_CandyContainer = new DisplayObjectContainer();
	container.AddChild(*m_CandyContainer);

	Image* image;
	int j = -1;
	int i;

	while (++j < m_NumRows)
	{
		i = -1;
		while (++i < m_NumCols)
		{
			image = new Image(*m_Atlas->GetTexture(TextureTypes::GRID_BGND));
			image->SetWidth(CELL_SIZE);
			image->SetHeight(CELL_SIZE);
			image->SetX(i * CELL_SIZE);
			image->SetY(j * CELL_SIZE);
			m_GridContainer->AddChild(*image);
		}
	}

	Stage& stage = *container.GetStage();
	float stageWidth = stage.GetStageWidth();
	float stageHeight = stage.GetStageHeight();

	container.SetWidth(0.9f * stageWidth);
	container.SetScaleY(container.GetScaleX());

	container.SetX(stageWidth / 2 - container.GetWidth() / 2);
	container.SetY(stageHeight / 2 - container.GetHeight() / 2);
}