#ifndef _GESTURE_H_
#define _GESTURE_H_

#include "EventDispatcher.h"
#include "Display.h"
#include "Updateable.h"

class GestureManager;

class Touch {};

class TouchesManager
{
private:
	GestureManager&		m_GestureManager;

public:
	explicit TouchesManager(GestureManager& gestureManager) : m_GestureManager(gestureManager) {}
	~TouchesManager() {}

	void OnTouchBegin(int x, int y);
	void OnTouchEnd(int x, int y);
	void OnTouchMove(int x, int y);
};


class InputAdapter : public IUpdateable
{
protected:
	TouchesManager*	m_TouchesManager;

public:
	void SetTouchesManager(TouchesManager& value) { m_TouchesManager = &value; };

public:
	InputAdapter() {}
	virtual ~InputAdapter() {}

	virtual void Update(float deltaTime = 0.0f) override {}
};


class Gesture
{
private:
	Display&	m_Target;

public:
	explicit Gesture(Display& target) : m_Target(target) {}
	virtual ~Gesture() {}

protected:
	void OnTouchBegin(Touch& touch) {};
	void OnTouchEnd(Touch& touch) {};
	void OnTouchMove(Touch& touch) {};
};

class TapGesture : public Gesture
{
public:
	explicit TapGesture(Display& target) : Gesture(target) {}
	~TapGesture() {}
};

class GestureMapItemSpecBase
{
private:
	Gesture&	m_Gesture;

public:
	explicit GestureMapItemSpecBase(Gesture& gesture) : m_Gesture(gesture) {}
	virtual ~GestureMapItemSpecBase() {}
};

template<class C>
class GestureMapItemSpec : public GestureMapItemSpecBase
{
private:
	C&		m_Proxy;
	void	(C::*m_Fct)(Event&);

public:
	explicit GestureMapItemSpec(Gesture& gesture) : GestureMapItemSpecBase(gesture) {}
	virtual ~GestureMapItemSpec() {}
};

class GestureMapItem
{
private:
	GestureMapItemSpecBase&	m_Spec;

public:
	template<class C>
	explicit GestureMapItem(Gesture& gesture) { m_Spec = new GestureMapItemSpec<C>(gesture); }
	~GestureMapItem() {}
};

class GestureManager
{
private:
	InputAdapter&		m_InputAdapater;
	TouchesManager*		m_TouchesManager;

public:
	explicit GestureManager(InputAdapter& inputAdapter);
	~GestureManager();

	template<class C, class G>
	G& AddGesture(Display& target, void (C::*fct)(Event&), C& proxy, const char* gestureType);

	template<class C>
	void RemoveGesture(Gesture& gesture, void (C::*fct)(Event&), C& proxy, const char* gestureType) {};

	template<class C>
	void RemoveAllGesturesOf(C& proxy) {};

	TapGesture& GetTapGesture(Display& target);

	void OnTouchBegin(Touch& touch) {};
	void OnTouchEnd(Touch& touch) {};
	void OnTouchMove(Touch& touch) {};

private:
	void RemoveAllGestures() {}
};

template<class C, class G>
G& GestureManager::AddGesture(Display& target, void (C::*fct)(Event&), C& proxy, const char* gestureType)
{
	Gesture* gesture = new G(target);

}




#endif