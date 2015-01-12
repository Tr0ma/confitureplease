#ifndef _BASEVIEW_H_
#define _BASEVIEW_H_

#include "DisplayObjectContainer.h"
#include "AssetManager.h"
#include "GestureManager.h"
#include "TweenManager.h"

#include <View.h>

class BaseView : public View
{
	friend class BaseMediator;

private:
	DisplayObjectContainer		m_Container;
	AssetManager*				m_AssetManager;
	GestureManager*				m_GestureManager;
	TweenManager*				m_TweenManager;

public:
	DisplayObjectContainer&		GetContainer()								{ return m_Container; }
	AssetManager&				GetAssetManager()							{ return *m_AssetManager; }
	GestureManager&				GetGestureManager()							{ return *m_GestureManager; }
	TweenManager&				GetTweenManager()							{ return *m_TweenManager; }

private:
	void						SetAssetManager(AssetManager& value)		{ m_AssetManager = &value; }
	void						SetGestureManager(GestureManager& value)	{ m_GestureManager = &value; }
	void						SetTweenManager(TweenManager& value)		{ m_TweenManager = &value; }

public:
	BaseView();
	~BaseView() {}

	virtual void	Show() final;

protected:
	virtual void	CreateView() {};
	virtual void	OnViewShown();

private:
	void	OnAddedToStage(const Event& evt);

	
};

#endif