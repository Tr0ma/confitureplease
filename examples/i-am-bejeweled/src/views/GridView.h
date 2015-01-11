#ifndef _GRIDVIEW_H_
#define _GRIDVIEW_H_

#include "BaseView.h"
#include "Image.h"

class GridView : public BaseView
{
private:
	Image* image;

public:
	static const char* ID;

public:
	GridView() {}
	~GridView();

protected:
	virtual void	CreateView() override;
};

#endif