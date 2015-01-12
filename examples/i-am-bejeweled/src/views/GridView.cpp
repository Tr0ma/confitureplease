#include "GridView.h"
#include "AtlasTypes.h"
#include "TextureTypes.h"
#include "Stage.h"
#include "SwipeGesture.h"
#include "GridSwipeViewEvent.h"
#include "GridViewEvent.h"

#include <iostream>
#include <Easing.h>

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

	Gem* gem = m_GemPool.Get();
	m_GemList.push_back(gem);

	Image* image = gem->m_Image;
	if (!image)
	{
		image = new Image(*m_Atlas->GetTexture(gemVO.m_Type));
		gem->m_Image = image;
	}
	else
	{
		image->SetTexture(*m_Atlas->GetTexture(gemVO.m_Type));
	}

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

void GridView::SwapThenCancel(GemVO& gemA, GemVO& gemB)
{
	DisplayObject* gemImageA = GetTargetbyGemVO(gemA);
	DisplayObject* gemImageB = GetTargetbyGemVO(gemB);

	PlaySwap(*gemImageA, *gemImageB, 0.1f);
	CancelSwap(*gemImageA, *gemImageB, 0.07f, 0.1f);
}

void GridView::SwapThenDelete(GemVO& gemA, GemVO& gemB, vector<GemVO*>& list)
{
	DisplayObject* gemImageA = GetTargetbyGemVO(gemA);
	DisplayObject* gemImageB = GetTargetbyGemVO(gemB);

	PlaySwap(*gemImageA, *gemImageB, 0.1f);
	PlayDelete(list, 0.2f, 0.1f);
}

void GridView::MoveDown(vector<GemVO*>& moveDownList, vector<GemVO*>& newGemsList)
{
	PlayMoveDown(moveDownList, 0.13f);
	PlayMoveDownNewGem(newGemsList, 0.13f, 0.13f);
}

void GridView::DeleteGems(vector<GemVO*>& list)
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

	GemVO& gemVO = *GetGemVOByTarget(swipeGesture.GetTarget());
	Vec2d direction(offset.x, offset.y);

	// normalize direction
	if (direction.x)
	{
		direction.x = direction.x / (direction.x < 0 ? -direction.x : direction.x);
	}

	if (direction.y)
	{
		direction.y = direction.y / (direction.y < 0 ? -direction.y : direction.y);
	}

	const GridSwipeViewEvent viewEvt(GridSwipeViewEvent::SWIPED, gemVO, direction);
	Dispatch(viewEvt);
}

GemVO* GridView::GetGemVOByTarget(const DisplayObject& target) const
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

GridView::Gem* GridView::GetGemByGemVO(const GemVO& gemVO) const
{
	int i = -1;
	int l = m_GemList.size();
	Gem* gem;

	while (i++ < l)
	{
		gem = m_GemList[i];
		if (gem->m_GemVO == &gemVO)
		{
			return gem;
		}
	}

	return nullptr;
}

DisplayObject* GridView::GetTargetbyGemVO(const GemVO& gemVO) const
{
	Gem* gem = GetGemByGemVO(gemVO);
	if (gem)
	{
		return gem->m_Image;
	}

	return nullptr;
}

int GridView::GetGemIndex(const Gem& gem)
{
	int i = -1;
	int l = m_GemList.size();

	while (i++ < l)
	{
		if ( m_GemList[i] == &gem)
		{
			return i;
		}
	}

	return -1;
}

void GridView::PlaySwap(DisplayObject& targetA, DisplayObject& targetB, float duration)
{
	TweenManager& tweenManager = GetTweenManager();
	TweenX& tweenXGemA = tweenManager.CreateTween<TweenX>(targetA);
	TweenX& tweenXGemB = tweenManager.CreateTween<TweenX>(targetB);
	TweenY& tweenYGemA = tweenManager.CreateTween<TweenY>(targetA);
	TweenY& tweenYGemB = tweenManager.CreateTween<TweenY>(targetB);

	tweenXGemA.From(targetA.GetX()).To(targetB.GetX()).Duration(duration).Easing(Linear::EaseNone).Play();
	tweenYGemA.From(targetA.GetY()).To(targetB.GetY()).Duration(duration).Easing(Linear::EaseNone).Play();
	tweenXGemB.From(targetB.GetX()).To(targetA.GetX()).Duration(duration).Easing(Linear::EaseNone).Play();
	tweenYGemB.From(targetB.GetY()).To(targetA.GetY()).Duration(duration).Easing(Linear::EaseNone).Play();
}

void GridView::CancelSwap(DisplayObject& targetA, DisplayObject& targetB, float duration, float delay)
{
	TweenManager& tweenManager = GetTweenManager();
	TweenX& tweenXGemA = tweenManager.CreateTween<TweenX>(targetA);
	TweenX& tweenXGemB = tweenManager.CreateTween<TweenX>(targetB);
	TweenY& tweenYGemA = tweenManager.CreateTween<TweenY>(targetA);
	TweenY& tweenYGemB = tweenManager.CreateTween<TweenY>(targetB);

	tweenXGemA.From(targetB.GetX()).To(targetA.GetX()).Duration(duration).Delay(delay).Easing(Linear::EaseNone).Play();
	tweenYGemA.From(targetB.GetY()).To(targetA.GetY()).Duration(duration).Delay(delay).Easing(Linear::EaseNone).Play();
	tweenXGemB.From(targetA.GetX()).To(targetB.GetX()).Duration(duration).Delay(delay).Easing(Linear::EaseNone).Play();
	tweenYGemB.From(targetA.GetY()).To(targetB.GetY()).Duration(duration).Delay(delay).Easing(Linear::EaseNone).Play();
}

void GridView::OnDeleteComplete(const Event& evt)
{
	int i = -1;
	const int l = m_DeleteList.size();
	Gem* gem;

	while (++i < l)
	{
		gem = m_DeleteList[i];
		m_CandyContainer->RemoveChild(*gem->m_Image);

		m_GemList.erase(m_GemList.begin() + GetGemIndex(*gem));
		m_GemPool.Release(gem);
	}

	m_DeleteList.clear();

	const GridViewEvent viewEvt(GridViewEvent::DELETE_COMPLETE);
	Dispatch(viewEvt);
}

void GridView::OnMoveDownComplete(const Event& evt)
{
	const GridViewEvent viewEvt(GridViewEvent::MOVE_DOWN_COMPLETE);
	Dispatch(viewEvt);
}

void GridView::PlayDelete(vector<GemVO*>& list, float duration, float delay)
{
	TweenManager& tweenManager = GetTweenManager();
	TweenScaleX* tweenScaleX;
	TweenScaleY* tweenScaleY;

	DisplayObject* gemImage;
	GemVO* gemVO;
	Gem* gem;

	m_DeleteList.clear();
	int i = -1;
	const int l = list.size();
	while (++i < l)
	{
		gemVO = list[i];
		gem = GetGemByGemVO(*gemVO);
		m_DeleteList.push_back(gem);

		gemImage = gem->m_Image;

		tweenScaleX = &tweenManager.CreateTween<TweenScaleX>(*gemImage);
		tweenScaleY = &tweenManager.CreateTween<TweenScaleY>(*gemImage);

		tweenScaleX->To(0.5f).Duration(duration).Delay(delay).Easing(Linear::EaseNone).Play();
		tweenScaleY->To(0.5f).Duration(duration).Delay(delay).Easing(Linear::EaseNone).Play();

		if (i == 0)
		{
			tweenScaleX->OnComplete(&GridView::OnDeleteComplete, *this);
		}
	}
}

void GridView::PlayMoveDown(vector<GemVO*>& list, float duration, float delay)
{
	TweenManager& tweenManager = GetTweenManager();
	TweenY* tweenY;
	Gem* gem;
	DisplayObject* gemImage;

	int i = -1;
	const int l = list.size();
	float y;
	while (++i < l)
	{
		gem = GetGemByGemVO(*list[i]);
		gemImage = gem->m_Image;

		y = (gem->m_GemVO->m_Y) * CELL_SIZE + CELL_SIZE / 2 - gemImage->GetHeight() / 2;

		tweenY = &tweenManager.CreateTween<TweenY>(*gemImage);
		tweenY->To(y).Duration(duration).Delay(delay).Easing(Linear::EaseNone).Play();

		if (i == 0)
		{
			tweenY->OnComplete(&GridView::OnMoveDownComplete, *this);
		}
	}
}

void GridView::PlayMoveDownNewGem(vector<GemVO*>& list, float duration, float delay)
{
	TweenManager& tweenManager = GetTweenManager();
	TweenY* tweenY;
	Gem* gem;
	GemVO* gemVO;
	DisplayObject* gemImage;

	int i = -1;
	const int l = list.size();

	while (++i < l)
	{
		gemVO = list[i];
		gem = &AddCell(gemVO->m_X, gemVO->m_Y, *gemVO);
		gemImage = gem->m_Image;

		//tweenY = &tweenManager.CreateTween<TweenY>(*gemImage);
		//tweenY->To(gem->m_Image->GetY()).Duration(duration).Delay(delay).Easing(Linear::EaseNone).Play();

		//gem->m_Image->SetY(-3 * CELL_SIZE + CELL_SIZE / 2 - gemImage->GetHeight() / 2);
	}
}