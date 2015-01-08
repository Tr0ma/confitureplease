#ifndef _INPUTADAPTER_H_
#define _INPUTADAPTER_H_

#include "Updateable.h"

class GestureManager;

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

#endif