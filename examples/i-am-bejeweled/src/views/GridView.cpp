#include "GridView.h"
#include "AtlasTypes.h"
#include "TextureTypes.h"
#include "Stage.h"

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

	DisplayObjectContainer& container = GetContainer();
	container.RemoveChild(*m_GridContainer);
	container.RemoveChild(*m_CandyContainer);

	delete m_GridContainer;
	delete m_CandyContainer;

	// should main container be removed here?
	container.GetParent()->RemoveChild(container);
}

void GridView::AddCell(int colId, int rowId, GemVO& gemVO)
{

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
	/*image = new Image(*m_Atlas->GetTexture(TextureTypes::GRID_BGND));
	image->SetX(10);
	container.GetStage()->AddChild(*image);*/

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

			
			/*int w = image->GetWidth();
			int h = image->GetHeight();*/

			/*image->SetX(i * image->GetWidth());
			image->SetY(j * image->GetHeight());*/
		}
	}

	Stage& stage = *container.GetStage();
	float stageWidth = stage.GetStageWidth();
	float stageHeight = stage.GetStageHeight();

	container.SetWidth(0.9f * stageWidth);
	container.SetScaleY(container.GetScaleX());

	//container.SetX(stageWidth / 2 - container.GetWidth() / 2);
	//container.SetY(stageHeight / 2 - container.GetHeight() / 2);
}