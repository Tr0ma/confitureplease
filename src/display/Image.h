#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "RenderSupport.h"

class Image
{
public:
	Image() {};
	virtual ~Image() {};

	virtual void Render(RenderSupport& renderSupport, float parentAlpha) {};
};

#endif