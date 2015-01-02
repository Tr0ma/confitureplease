#ifndef _TESTS_H_
#define _TESTS_H_

#include "Gesture.h"
#include "s3eInputAdapter.h"
#include "Iw2DSceneGraph.h"
#include "CFSprite.h"

using namespace Iw2DSceneGraph;
using namespace Iw2DSceneGraphCore;

class GestureTest
{
private:
	CNode*		m_Scene;

	CIw2DImage* m_ImageUp;
	CIw2DImage* m_ImageDown;

	CFSprite*	m_UpButton;
	CFSprite*	m_DownButton;

	s3eInputAdapter* inputAdapater;
	GestureManager* gestureManager;

	TapGesture*	m_DownTap;
	TapGesture*	m_UpTap;

public:
	GestureTest();
	~GestureTest();

	void OnUpTap(Event& evt);
	void OnDownTap(Event& evt);

	void Update(float deltaTime);
	void Render();
};

#endif


