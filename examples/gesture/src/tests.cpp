#include "tests.h"
#include "s3eInputAdapter.h"
#include <iostream>

using namespace std;

GestureTest::GestureTest()
{
	m_Scene = new CNode();

	m_ImageUp = Iw2DCreateImage("textures/button_up.png");
	m_ImageDown = Iw2DCreateImage("textures/button_down.png");

	m_UpButton = new CFSprite();
	m_UpButton->SetImage(m_ImageUp);
	m_UpButton->SetWidth(static_cast<int>(m_ImageUp->GetWidth()));
	m_UpButton->SetHeight(static_cast<int>(m_ImageUp->GetHeight()));

	m_DownButton = new CFSprite();
	m_DownButton->SetImage(m_ImageDown);
	m_DownButton->SetAlpha(0);
	m_DownButton->SetWidth(static_cast<int>(m_ImageUp->GetWidth()));
	m_DownButton->SetHeight(static_cast<int>(m_ImageUp->GetHeight()));

	m_Scene->AddChild(&(m_DownButton->GetSprite()));
	m_Scene->AddChild(&(m_UpButton->GetSprite()));
	
	inputAdapater = new s3eInputAdapter();
	gestureManager = new GestureManager(*inputAdapater);

	m_UpTap = &(gestureManager->AddGesture<TapGesture>(*m_UpButton, &GestureTest::OnUpTap, *this));
	m_DownTap = &(gestureManager->AddGesture<TapGesture>(*m_DownButton, &GestureTest::OnDownTap, *this));
	m_DownTap->SetEnabled(false);
}

GestureTest::~GestureTest()
{
	delete gestureManager;
	delete inputAdapater;

	delete m_DownButton;
	delete m_UpButton;

	delete m_ImageDown;
	delete m_ImageUp;

	delete m_Scene;
}

void GestureTest::OnUpTap(Event& evt)
{
	m_UpButton->SetAlpha(0);
	m_DownButton->SetAlpha(1.0f);

	m_DownTap->SetEnabled(true);
	m_UpTap->SetEnabled(false);
}

void GestureTest::OnDownTap(Event& evt)
{
	m_DownButton->SetAlpha(0);
	m_UpButton->SetAlpha(1.0f);

	m_DownTap->SetEnabled(false);
	m_UpTap->SetEnabled(true);
}

void GestureTest::Update(float deltaTime)
{
	gestureManager->Update(deltaTime);
	m_Scene->Update(deltaTime);
}

void GestureTest::Render()
{
	m_Scene->Render();
}

