#include "tests.h"
#include <iostream>
#include "Matrix.h"
#include "Confiture.h"
#include "Iw2D.h"

using namespace std;

Tests::Tests()
{
	Matrix mat;

	Rectangle viewport = Rectangle(0, 0, Iw2DGetSurfaceWidth(),Iw2DGetSurfaceHeight());
	m_Confiture = new Confiture(viewport);
}

Tests::~Tests()
{
	delete m_Confiture;
}

void Tests::Update(float deltaTime)
{
	m_Confiture->Update(deltaTime);
}

void Tests::Render()
{
	m_Confiture->Render();
}