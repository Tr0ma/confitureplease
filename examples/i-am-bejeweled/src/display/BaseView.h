#ifndef _BASEVIEW_H_
#define _BASEVIEW_H_

#include "DisplayObjectContainer.h"
#include "AssetManager.h"
#include "GestureManager.h"
#include <View.h>

class BaseView : public View
{
	friend class BaseMediator;

private:
	DisplayObjectContainer		m_Container;
	AssetManager*				m_AssetManager;
	GestureManager*				m_GestureManager;

public:
	DisplayObjectContainer&		GetContainer()							{ return m_Container; }
	AssetManager&				GetAssetManager()						{ return *m_AssetManager; }
	GestureManager&				GetGestureManager()						{ return *m_GestureManager; }

private:
	void						SetAssetManager(AssetManager& value)	{ m_AssetManager = &value; }
	void						SetAssetManager(GestureManager& value)	{ m_GestureManager = &value; }

public:
	BaseView();
	~BaseView() {}

	virtual void	Show() final;

protected:
	virtual void	CreateView() {};
	
};

#endif