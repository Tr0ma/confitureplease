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
	 static void     TouchButtonCB(s3ePointerEvent* event, void*);
	 static void     TouchMotionCB(s3ePointerMotionEvent* event, void*);
	 static void     MultiTouchButtonCB(s3ePointerTouchEvent* event, void*);
	 static void     MultiTouchMotionCB(s3ePointerTouchMotionEvent* event, void*);
};

#endif