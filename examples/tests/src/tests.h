#ifndef _TESTS_H_
#define _TESTS_H_

#include "EventDispatcher.h"

class GestureTest
{
public:
	GestureTest();
	~GestureTest() {}

	void OnTap(Event& evt) {};
};

class Tests
{

public:
	Tests();
	~Tests();

	void Update(float deltaTime);

	
};

#endif


