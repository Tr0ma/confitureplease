#ifndef _DISPLAYOBJECT_H_
#define _DISPLAYOBJECT_H_

#include "RenderSupport.h"

class DisplayObject
{
public:
	DisplayObject() {};
	virtual ~DisplayObject() {};

	virtual void Render(RenderSupport& renderSupport, float parentAlpha) {};
};

#endif