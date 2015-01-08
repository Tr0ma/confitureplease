#ifndef _GESTURE_H_
#define _GESTURE_H_

#include "EventDispatcher.h"
#include "DisplayObject.h"
#include "Updateable.h"
#include "Stage.h"

class GestureManager;


class GestureEvent : public Event
{
public:
	static const char* GESTURE_RECOGNIZED;

public:
	explicit GestureEvent(const char* type) : Event(type) {}
	~GestureEvent() {};
};


class InputAdapter : public IUpdateable
{
protected:
	GestureManager*		m_GestureManager;

public:
	GestureManager&		GetGestureManager()							{ return *m_GestureManager; }
	void				SetGestureManager(GestureManager& value)	{ m_GestureManager = &value; }

public:
	InputAdapter() {}
	virtual ~InputAdapter() {}

	virtual void Update(float deltaTime = 0.0f) override {}
};


class Gesture : public EventDispatcher
{
private:
	DisplayObject&	m_Target;
	bool			m_Enabled;

protected:
	int				m_TouchCount;

	enum GestureState
	{
		BEGAN,
		ENDED
	};

	GestureState	m_State;

public:
	DisplayObject&	GetTarget() { return m_Target; }

	bool		GetEnabled()			{ return m_Enabled; }
	void		SetEnabled(bool value)	{ m_Enabled = value; }

public:
	explicit Gesture(DisplayObject& target) : m_Target(target), m_TouchCount(0) {}
	virtual ~Gesture() {}

	void BeginTouch(Vec2d point);
	void EndTouch(Vec2d point);
	void MoveTouch(Vec2d point);

protected:
	void SetState(GestureState state);

	virtual void OnTouchBegin(Vec2d point) {}
	virtual void OnTouchEnd(Vec2d point) {}
	virtual void OnTouchMove(Vec2d point) {}
};


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


class GestureMapItemSpecBase
{
private:
	Gesture&	m_Gesture;

public:
	Gesture&	GetGesture() { return m_Gesture; }

public:
	explicit GestureMapItemSpecBase(Gesture& gesture) : m_Gesture(gesture) {}
	virtual ~GestureMapItemSpecBase() {}

	virtual void operator()(Event& evt) {}
};

template<class C>
class GestureMapItemSpec : public GestureMapItemSpecBase
{
private:
	C&		m_Proxy;
	void	(C::*m_Fct)(Event&);

public:
	C&		GetProxy()					{ return m_Proxy; }
	void	(C::*GetFunction())(Event&) { return m_Fct; };

public:
	explicit GestureMapItemSpec(Gesture& gesture, C& proxy, void (C::*fct)(Event&)) 
		: GestureMapItemSpecBase(gesture), m_Proxy(proxy), m_Fct(fct) {}
	virtual ~GestureMapItemSpec() {}

	void operator()(Event& evt) override	{ (&m_Proxy->*m_Fct)(evt); }
};


class GestureMapItem
{
private:
	Gesture& m_Gesture;

public:
	Gesture&	GetGesture() { return m_Gesture; }

public:
	explicit GestureMapItem(Gesture& gesture) : m_Gesture(gesture) {}
	~GestureMapItem() {}
};


class GestureManager : public IUpdateable
{
private:
	InputAdapter&			m_InputAdapater;
	vector<GestureMapItem*>	m_Items;
    Stage&                  m_Stage;

public:
	explicit GestureManager(InputAdapter& inputAdapter, Stage& stage);
	~GestureManager() {};

	template<class G, class C>
	G& AddGesture(DisplayObject& target, void (C::*fct)(Event&), C& proxy);

	template<class C>
	void RemoveGesture(Gesture& gesture, void (C::*fct)(Event&), C& proxy, const char* gestureType) {};

	template<class C>
	void RemoveAllGesturesOf(C& proxy) {};

	TapGesture& GetTapGesture(DisplayObject& target);
    void AddHitTester();
    void Update(float deltaTime = 0.0f) override;

	void OnTouchBegin(Vec2d point);
	void OnTouchEnd(Vec2d point);
	void OnTouchMove(Vec2d point);

private:
	void RemoveAllGestures() {}
};

template<class G, class C>
G& GestureManager::AddGesture(DisplayObject& target, void (C::*fct)(Event&), C& proxy)
{
	G* gesture = new G(target);
	gesture->AddListener(GestureEvent::GESTURE_RECOGNIZED, fct, proxy);
	GestureMapItem* item = new GestureMapItem(*gesture);
	m_Items.push_back(item);
	return *gesture;
}


#endif