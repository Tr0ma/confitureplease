#ifndef _GESTUREMANAGER_H_
#define _GESTUREMANAGER_H_

#include "Gesture.h"
#include "GestureEvent.h"
#include "Updateable.h"
#include "InputAdapter.h"
#include "TapGesture.h"
#include "Touch.h"
#include <vector>

using namespace std;

class TouchesManager;
class Stage;

class GestureMapItem
{
public:
    DisplayObject&      m_Target;
    vector<Gesture*>    m_GestureList;

public:
	explicit GestureMapItem(DisplayObject& target) : m_Target(target) {}
	~GestureMapItem() {}
};

class TouchMapItem
{
public:
    Touch*              m_Touch;
    vector<Gesture*>    m_GestureList;
};


class GestureManager : public IUpdateable
{
private:
	InputAdapter&				m_InputAdapater;
	TouchesManager*				m_TouchesManager;
	vector<GestureMapItem*>		m_GestureMapItems;
    vector<TouchMapItem*>       m_TouchMapItems;
    Stage&						m_Stage;

public:
	explicit GestureManager(InputAdapter& inputAdapter, Stage& stage);
	~GestureManager() {}

	template<class G, class C>
	G& AddGesture(DisplayObject& target, void (C::*fct)(Event&), C& proxy);

	template<class C>
	void RemoveGesture(Gesture& gesture, void (C::*fct)(Event&), C& proxy, const char* gestureType) {};

	template<class C>
	void RemoveAllGesturesOf(C& proxy) {};

	TapGesture& GetTapGesture(DisplayObject& target);
    void Update(float deltaTime = 0.0f) override;

	void OnTouchBegin(Touch& touch);
	void OnTouchEnd(Touch& point);
	void OnTouchMove(Touch& point);

private:
	void            RemoveAllGestures() {}
    GestureMapItem* GetGestureMapItemByTarget(DisplayObject& target);
    TouchMapItem*   GetTouchMapItemByTouch(Touch& touch);
    int             GetTouchMapItemIndexByTouch(Touch& touch);
    void            GetHierarchy(DisplayObject& target, vector<DisplayObject*>& result);
};

template<class G, class C>
G& GestureManager::AddGesture(DisplayObject& target, void (C::*fct)(Event&), C& proxy)
{
	G* gesture = new G(target);
	gesture->AddListener(GestureEvent::GESTURE_RECOGNIZED, fct, proxy);

    GestureMapItem* item = GetGestureMapItemByTarget(target);
    if (!item)
    {
        item = new GestureMapItem(target);
        m_GestureMapItems.push_back(item);
    }

    item->m_GestureList.push_back(gesture);
	return *gesture;
}



#endif