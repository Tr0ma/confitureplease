#include "tests.h"
#include <iostream>
#include "Confiture.h"
#include "Iw2D.h"

using namespace std;

Tests::Tests()
{
	Rectangle viewport = Rectangle(0, 0, Iw2DGetSurfaceWidth(),Iw2DGetSurfaceHeight());
	//m_Confiture = new Confiture(viewport);

	m_AssetManager = new AssetManager();
	m_AssetManager->AddAtlas("my-atlas", "atlas/my-atlas.png", "atlas/my-atlas.json");
}

Tests::~Tests()
{
	delete m_AssetManager;
	//delete m_Confiture;
}

void Tests::Update(float deltaTime)
{
	//m_Confiture->Update(deltaTime);
}

void Tests::Render()
{
	//m_Confiture->Render();
}