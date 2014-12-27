#ifndef _S3EINPUTADAPTER_H_
#define _S3EINPUTADAPTER_H_

#include "Gesture.h"
#include "s3ePointer.h"

class s3eInputAdapter : public InputAdapter
{
public:
	s3eInputAdapter();
	~s3eInputAdapter() {}

	virtual void Update(float deltaTime = 0.0f) override;

private:
	 void     TouchButtonCB(s3ePointerEvent* event);
	 void     TouchMotionCB(s3ePointerMotionEvent* event);
	 void     MultiTouchButtonCB(s3ePointerTouchEvent* event);
	 void     MultiTouchMotionCB(s3ePointerTouchMotionEvent* event);
};

#endif