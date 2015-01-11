#include "Confiture.h"

const char* Confiture::CONFITURE_ID = "Confiture_CONFITURE_ID";

Confiture::Confiture(Rectangle viewport) : m_Viewport(viewport)
{
	m_Stage = new Stage(viewport.m_Width, viewport.m_Height);
}

Confiture::~Confiture()
{
	delete m_Stage;
}

void Confiture::Update(float deltaTime)
{
	// is there anything to update ?
}

void Confiture::Render()
{
	m_RenderSupport.NextFrame();

	m_Stage->Render(m_RenderSupport, 1.0f);

	// consider displaying stats here by getting draw count
}