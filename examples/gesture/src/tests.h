#ifndef _TESTS_H_
#define _TESTS_H_

#include "Confiture.h"
#include "AssetManager.h"
#include "Gesture.h"
#include "GestureManager.h"
#include "s3eInputAdapter.h"

class GestureTest
{
private:
	Confiture*			m_Confiture;
	AssetManager*		m_AssetManager;

	Image*				m_UpButton;
	Image*				m_DownButton;

	s3eInputAdapter*	m_InputAdapter;
	GestureManager*		m_GestureManager;

	TapGesture*			m_DownTap;
	TapGesture*			m_UpTap;

public:
	GestureTest();
	~GestureTest();

	void OnUpTap(Event& evt);
	void OnDownTap(Event& evt);

	void Update(float deltaTime);
	void Render();
};

#endif


