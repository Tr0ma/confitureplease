#ifndef _TESTS_H_
#define _TESTS_H_

#include "Confiture.h"
#include "AssetManager.h"

class Tests
{
private:
	Confiture*		m_Confiture;
	AssetManager*	m_AssetManager;

public:
	Tests();
	~Tests();

	void Update(float deltaTime);
	void Render();
};

#endif


