#include "BaseView.h"

BaseView::BaseView()
{
	m_Container.SetVisible(false);
}

void BaseView::Show()
{
	m_Container.SetVisible(true);
}