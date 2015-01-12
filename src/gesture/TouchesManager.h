#ifndef _TOUCHESMANAGER_H_
#define _TOUCHESMANAGER_H_

#include "Updateable.h"
#include "Touch.h"
#include "GestureManager.h"
#include "Vec2d.h"

#include <vector>

using namespace std;

class TouchesManager : public Updateable
{
private:
	vector<Touch*>		m_TouchList;
	GestureManager&		m_GestureManager;
	Stage&				m_Stage;
	unsigned int		m_ActiveTouchesCount;

protected:
	static long			timeHelper;

public:
	explicit TouchesManager(GestureManager& gestureManager, Stage& stage) 
		: m_GestureManager(gestureManager), m_Stage(stage), m_ActiveTouchesCount(0) {}
	
	~TouchesManager();

	void	OnTouchBegin(int touchID, Vec2d& point);
	void	OnTouchEnd(int touchID, Vec2d& point);
	void	OnTouchMove(int touchID, Vec2d& point);

private:
	Touch*	GetTouchByTouchID(int touchID);
	int		GetIndexByTouchID(int touchID);
};

#endif