#ifndef _DISPLAYOBJECTCONTAINER_H_
#define _DISPLAYOBJECTCONTAINER_H_

#include "DisplayObject.h"
#include <vector>

using namespace std;

class DisplayObjectContainer : public DisplayObject
{
private:
	vector<DisplayObject*>	m_Children;
	int						m_NumChildren;

public:
	DisplayObjectContainer() : m_NumChildren(0) {};
	~DisplayObjectContainer() {};

	virtual DisplayObject&	AddChild(DisplayObject& child);
	virtual DisplayObject&	AddChildAt(DisplayObject& child, int index);
	virtual DisplayObject&	RemoveChild(DisplayObject& child);
	virtual DisplayObject&	RemoveChildAt(int index);
	DisplayObject&			GetChildAt(int index);
	int						GetChildIndex(DisplayObject& child);

	virtual void Render(RenderSupport& renderSupport, float parentAlpha) override;

private:
	DisplayObject& CleanChild(DisplayObject& child, int index);
};

#endif