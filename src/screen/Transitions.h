#ifndef _TRANSITIONS_H_
#define _TRANSITIONS_H_

#include "EventDispatcher.h"
#include "TweenManager.h"

class DisplayObject;

class Transition : public EventDispatcher
{
public:
	static const float DEFAULT_ANIMATION_TIME;

protected:
	DisplayObject*		m_NextScreen;
	DisplayObject*		m_PreviousScreen;
	TweenManager*		m_TweenManager;

public:
	void	SetNextScreen(DisplayObject& value)		{ m_NextScreen = &value; };
	void	SetPreviousScreen(DisplayObject& value)	{ m_PreviousScreen = &value; };
	void	SetTweenManager(TweenManager& value)		{ m_TweenManager = &value; };

public:
	explicit Transition() {}
	virtual ~Transition() {}

	virtual void Play() {};
	virtual void Stop() {};
	virtual void Reverse() {};

protected:
	virtual void OnTransitionComplete(const Event& evt);
};

class MoveLeft : public Transition
{

public:
	explicit MoveLeft() {}
	virtual ~MoveLeft() {}

	void Play() override;
	void Stop() override;
	void Reverse() override;

protected:
	void OnTransitionComplete(const Event& evt) override { Transition::OnTransitionComplete(evt); };
};


class TransitionEvent : public Event
{
public:
	static const char* COMPLETE;

public:
	explicit TransitionEvent(const char* type) : Event(type) {}
	virtual ~TransitionEvent() {}	
};


class TransitionFactory
{
	static MoveLeft& MOVE_LEFT() { return *(new MoveLeft()); }
};

#endif
