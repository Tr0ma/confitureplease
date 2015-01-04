#ifndef _STAGE_H_
#define _STAGE_H_

#include "DisplayObjectContainer.h"

class Stage: public DisplayObjectContainer
{
private:
	int m_Width;
	int m_Height;

public:
	Stage(int width, int height) : m_Width(width), m_Height(height) {};
	~Stage() {};
};

#endif