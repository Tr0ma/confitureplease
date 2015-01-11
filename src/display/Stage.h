#ifndef _STAGE_H_
#define _STAGE_H_

#include "DisplayObjectContainer.h"

class Stage: public DisplayObjectContainer
{
private:
	float m_Width;
	float m_Height;

public:
	Stage(float width, float height) : m_Width(width), m_Height(height) {}
	~Stage();

    virtual DisplayObject*	HitTest(Vec2d localPoint) override;
};

#endif