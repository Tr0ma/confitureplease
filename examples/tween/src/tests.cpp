#include "tests.h"
#include <iostream>

#include "Easing.h"
#include "CFSprite.h"

using namespace std;

TweenTest::TweenTest()
{
	tweenManager = new TweenManager();
	display = new CFSprite();

	TweenX& tweenX = tweenManager->CreateTween<TweenX>(*display);
	tweenX.AddListener(TweenEvent::START, &TweenTest::onTweenStart, *this);

	tweenX
		.From(0).To(60).Duration(3.0f)
		.Delay(1.0f)
		.Easing(Linear::EaseNone)
		.OnComplete(&TweenTest::onTweenComplete, *this)
		.OnUpdate(&TweenTest::onTweenUpdate, *this)
		.Play();

	//tween.Stop();

	/*Timeline timeline = new Timeline();
	timeline.AddEventListener(TimelineEvent::PLAY, onStart);
	timeline.AddEventListener(TimelineEvent::STOP, onStop);
	timeline.AddEventListener(TimelineEvent::COMPLETE, onComplete);

	timeline.insert(new Tween(display, 0.3, TweenX.from(0).to(100), ease), 0.2);
	timeline.insert(new Tween(display, 0.3, TweenY.from(0).to(100), ease), 0.2);

	tween.play();*/
}

TweenTest::~TweenTest()
{
	delete tweenManager;
	delete display;
}

void TweenTest::onTweenStart(Event& evt)
{
	
}

void TweenTest::onTweenUpdate(Event& evt)
{
	
}

void TweenTest::onTweenComplete(Event& evt)
{
	
}

void TweenTest::Update(float deltaTime)
{
	tweenManager->Update(deltaTime);

	cout << display->GetX() << endl;
}

