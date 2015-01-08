#ifndef _TAPGESTURE_H_
#define _TAPGESTURE_H_

#include "Gesture.h"

class TapGesture : public Gesture
{
public:
	explicit TapGesture(DisplayObject& target) : Gesture(target) {}
	~TapGesture() {}

protected:
	virtual void OnTouchBegin(Vec2d point) override;
	virtual void OnTouchEnd(Vec2d point) override;
	virtual void OnTouchMove(Vec2d point) override;
};

#endif