#include "BaseView.h"
#include "ViewEvent.h"
#include "DisplayObjectEvent.h"

BaseView::BaseView()
{
	m_Container.AddListener(DisplayObjectEvent::ADDED_TO_STAGE, &BaseView::OnAddedToStage, *this);
	m_Container.SetVisible(false);
}

void BaseView::Show()
{
	m_Container.SetVisible(true);
	OnViewShown();
}

void BaseView::OnViewShown()
{
	const ViewEvent evt(ViewEvent::VIEW_SHOWN);
	Dispatch(evt);
}

void BaseView::OnAddedToStage(const Event& evt)
{
	m_Container.RemoveListener(DisplayObjectEvent::ADDED_TO_STAGE, &BaseView::OnAddedToStage, *this);
	CreateView();
}