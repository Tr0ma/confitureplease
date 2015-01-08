#include "tests.h"
#include "s3eInputAdapter.h"
#include "Image.h"
#include <iostream>

using namespace std;

GestureTest::GestureTest()
{
	Rectangle viewport = Rectangle(0, 0, Iw2DGetSurfaceWidth(), Iw2DGetSurfaceHeight());
	m_Confiture = new Confiture(viewport);

	m_AssetManager = new AssetManager();
	m_AssetManager->AddAtlas("my-atlas", "atlas/my-atlas.png", "atlas/my-atlas.json");

	Atlas* atlas = m_AssetManager->GetTextureAtlas("my-atlas");

	m_UpButton = new Image(*(atlas->GetTexture("blue.png")));
	m_Confiture->GetStage().AddChild(*m_UpButton);

	m_DownButton = new Image(*(atlas->GetTexture("green.png")));
	m_DownButton->SetAlpha(0);
	m_DownButton->SetTouchable(false);
	m_Confiture->GetStage().AddChild(*m_DownButton);

	m_InputAdapter = new s3eInputAdapter();
	m_GestureManager = new GestureManager(*m_InputAdapter, m_Confiture->GetStage());

	m_UpTap = &(m_GestureManager->AddGesture<TapGesture>(*m_UpButton, &GestureTest::OnUpTap, *this));
	m_DownTap = &(m_GestureManager->AddGesture<TapGesture>(*m_DownButton, &GestureTest::OnDownTap, *this));
}

GestureTest::~GestureTest()
{
	delete m_GestureManager;
	delete m_InputAdapter;

	delete m_DownButton;
	delete m_UpButton;
}

void GestureTest::OnUpTap(Event& evt)
{
	GestureTest* test = this;

	m_UpButton->SetAlpha(0);
	m_UpButton->SetTouchable(false);

	m_DownButton->SetAlpha(1.0f);
	m_DownButton->SetTouchable(true);
}

void GestureTest::OnDownTap(Event& evt)
{
	m_DownButton->SetAlpha(0);
	m_DownButton->SetTouchable(false);

	m_UpButton->SetAlpha(1.0f);
	m_UpButton->SetTouchable(true);
}

void GestureTest::Update(float deltaTime)
{
	//m_GestureManager->Update(deltaTime);
	m_Confiture->Update(deltaTime);
}

void GestureTest::Render()
{
	m_Confiture->Render();
}

