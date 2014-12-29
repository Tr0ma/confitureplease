#ifndef _TESTS_H_
#define _TESTS_H_

#include "EventDispatcher.h"
#include "Gesture.h"
#include "s3eInputAdapter.h"

class GestureTest
{
private:
	Display* display;
	s3eInputAdapter* inputAdapater;
	GestureManager* gestureManager;

public:
	GestureTest();
	~GestureTest();

	void OnTap(Event& evt) {};

	void Update(float deltaTime);
};

class Tests
{
private:
	GestureTest* test;

public:
	Tests();
	~Tests();

	void Update(float deltaTime);
};

#endif


