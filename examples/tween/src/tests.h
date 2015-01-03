#ifndef _TESTS_H_
#define _TESTS_H_

#include "Display.h"
#include "TweenManager.h"

class TweenTest
{
public:
	Container*		display;
	TweenManager*	tweenManager;

public:
	TweenTest();
	~TweenTest();

	void onTweenStart(Event& evt);
	void onTweenUpdate(Event& evt);
	void onTweenComplete(Event& evt);

	void Update(float deltaTime);
};

#endif


