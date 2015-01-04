#ifndef _TESTS_H_
#define _TESTS_H_

#include "Confiture.h"

class Tests
{
private:
	Confiture* m_Confiture;

public:
	Tests();
	~Tests();

	void Update(float deltaTime);
	void Render();
};

#endif


