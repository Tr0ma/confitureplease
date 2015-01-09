#ifndef _INPUTADAPTER_H_
#define _INPUTADAPTER_H_

#include "Updateable.h"

class TouchesManager;

class InputAdapter : public IUpdateable
{
protected:
	TouchesManager*		m_TouchesManager;

public:
	TouchesManager&		GetTouchesManager()							{ return *m_TouchesManager; }
	void				SetTouchesManager(TouchesManager& value)	{ m_TouchesManager = &value; }

public:
	InputAdapter() {}
	virtual ~InputAdapter() {}

	virtual void Update(float deltaTime = 0.0f) override {}
};

#endif