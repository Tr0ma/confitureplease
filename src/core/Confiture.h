#ifndef _CONFITURE_H_
#define _CONFITURE_H_

#include "RenderSupport.h"
#include "Stage.h"
#include "Rectangle.h"
#include "Updateable.h"
#include "Renderable.h"

class Confiture : public IUpdateable, public IRenderable
{
private:
	Stage*			m_Stage;
	RenderSupport	m_RenderSupport;
	Rectangle		m_Viewport;

public:
	Stage&	GetStage() { return *m_Stage; }

public:
	explicit Confiture(Rectangle viewport);
	~Confiture();

	void Update(float deltaTime) override;

	void Render() override;
};

#endif