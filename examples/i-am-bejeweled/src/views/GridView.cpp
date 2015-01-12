#include "GridView.h"
#include "AtlasTypes.h"
#include "TextureTypes.h"
#include "Stage.h"
#include "SwipeGesture.h"
#include "GridSwipeViewEvent.h"

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

	GestureManager& gestureManager = GetGestureManager();
	Gem* gem;
	Image* image;
	SwipeGesture* gesture;

	j = m_GemList.size();
	while (--j >= 0)
	{
		gem = m_GemList[j];
		image = gem->m_Image;
		gesture = gem->m_Gesture;

		m_CandyContainer->RemoveChild(*image);
		gestureManager.RemoveGesture(*gesture, &GridView::OnSwipe, *this);
		
		delete gesture;
		delete image;
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

	GestureManager& gestureManager = GetGestureManager();
	SwipeGesture* swipeGesture = &(gestureManager.AddGesture<SwipeGesture>(*image, &GridView::OnSwipe, *this));

	gem->m_Image = image;
	gem->m_GemVO = &gemVO;
	gem->m_Gesture = swipeGesture;

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

void GridView::OnSwipe(const Event& evt)
{
	const GestureEvent& gestureEvent = static_cast<const GestureEvent&>(evt);
	const SwipeGesture& swipeGesture = static_cast<const SwipeGesture&>(gestureEvent.m_Gesture);
	const Vec2d& offset = swipeGesture.GetOffset();
	//cout << "x : " << swipeGesture.GetOffset().x << " , y : " << swipeGesture.GetOffset().y << endl;

	GemVO& gemVO = *GetGemByTarget(swipeGesture.GetTarget());
	Vec2d direction(offset.x, offset.y);

	direction.x = direction.x < 0 ? -direction.x : direction.x;
	direction.y = direction.y < 0 ? -direction.y : direction.y;

	const GridSwipeViewEvent viewEvt(GridSwipeViewEvent::SWIPED, gemVO, direction);
	Dispatch(viewEvt);
}

GemVO* GridView::GetGemByTarget(const DisplayObject& target) const
{
	int i = -1;
	int l = m_GemList.size();
	Gem* gem;

	while (i++ < l)
	{
		gem = m_GemList[i];
		if (gem->m_Image == &target)
		{
			return gem->m_GemVO;
		}
	}

	return nullptr;
}