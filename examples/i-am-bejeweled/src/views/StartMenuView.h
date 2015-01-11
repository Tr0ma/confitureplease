#ifndef _STARTMENUVIEW_H_
#define _STARTMENUVIEW_H_

#include "BaseView.h"
#include "Image.h"

class StartMenuView : public BaseView
{
private:
	Image* image;

public:
	static const char* STARTMENU_VIEW;

public:
	StartMenuView() {}
	~StartMenuView();

protected:
	virtual void	CreateView() override;
};

#endif