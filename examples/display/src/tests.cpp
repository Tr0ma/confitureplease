#include "tests.h"
#include <iostream>
#include "Confiture.h"
#include "Iw2D.h"
#include "Image.h"
#include <math.h>

using namespace std;

Tests::Tests()
{
	Rectangle viewport = Rectangle(0, 0, Iw2DGetSurfaceWidth(),Iw2DGetSurfaceHeight());
	m_Confiture = new Confiture(viewport);

	m_AssetManager = new AssetManager();
	m_AssetManager->AddAtlas("my-atlas", "atlas/my-atlas.png", "atlas/my-atlas.json");

	Atlas* atlas = m_AssetManager->GetTextureAtlas("my-atlas");

	DisplayObjectContainer* topContainer = new DisplayObjectContainer();
	topContainer->SetScaleX(0.5f);
	topContainer->SetX(100);
	m_Confiture->GetStage().AddChild(*topContainer);

	DisplayObjectContainer* container = new DisplayObjectContainer();
	container->SetScaleY(0.5f);
	topContainer->AddChild(*container);

	Image* image = new Image(*(atlas->GetTexture("blue.png")));
	//container->AddChild(*image);

	//topContainer->SetRotation(PI / 8);
	container->AddChild(*image);
}

Tests::~Tests()
{
	delete m_AssetManager;
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