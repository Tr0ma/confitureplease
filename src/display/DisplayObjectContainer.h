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
	DisplayObjectContainer() {};
	~DisplayObjectContainer() {};

	virtual void Render(RenderSupport& renderSupport, float parentAlpha) override;
};

#endif