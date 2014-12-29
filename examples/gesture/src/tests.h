#ifndef _TESTS_H_
#define _TESTS_H_

#include "EventDispatcher.h"
#include "Gesture.h"
#include "s3eInputAdapter.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;
using namespace Iw2DSceneGraphCore;

class CFSprite : public Display
{
private:
	int m_ScreenWidth;
	int m_ScreenHeight;

	CSprite m_Sprite;

public:
	CFSprite() {}
	~CFSprite() {}

	CSprite&	GetSprite()							{ return m_Sprite; }

	int			GetX() override						{ return static_cast<int>(m_Sprite.m_X); }
	void		SetX(int value)	override			{ m_Sprite.m_X = static_cast<float>(value); }

	int			GetY() override						{ return static_cast<int>(m_Sprite.m_Y); }
	void		SetY(int value)	override			{ m_Sprite.m_Y = static_cast<float>(value); }

	int			GetWidth() override					{ return static_cast<int>(m_Sprite.m_W); }
	void		SetWidth(int value)	override		{ m_Sprite.m_W = static_cast<float>(value); }

	int			GetHeight() override				{ return static_cast<int>(m_Sprite.m_H); }
	void		SetHeight(int value) override		{ m_Sprite.m_H = static_cast<float>(value); }

	float		GetRotation() override				{ return m_Sprite.m_Angle; }
	void		SetRotation(float value) override	{ m_Sprite.m_Angle = value; }

	float		GetScaleX() override				{ return m_Sprite.m_ScaleX; }
	void		SetScaleX(float value) override		{ m_Sprite.m_ScaleX = value; }

	float		GetScaleY() override				{ return m_Sprite.m_ScaleY; }
	void		SetScaleY(float value) override		{ m_Sprite.m_ScaleY = value; }

	float		GetAlpha() override					{ return m_Sprite.m_Alpha; }
	void		SetAlpha(float value) override		{ m_Sprite.m_Alpha = value; }

	int			GetScreenWidth() override			{ return m_ScreenWidth; }
	void		SetScreenWidth(int value) override	{ m_ScreenWidth = value; }

	int			GetScreenHeight() override			{ return m_ScreenHeight; }
	void		SetScreenHeight(int value) override	{ m_ScreenHeight = value; }

	bool		HitTest(int x, int y) override		{ return m_Sprite.HitTest(x, y); }
	void		SetImage(CIw2DImage* pImage)		{ m_Sprite.SetImage(pImage); }
	
};

class GestureTest
{
private:
	CNode*		m_Scene;

	CIw2DImage* m_ImageUp;
	CIw2DImage* m_ImageDown;

	CFSprite*	m_UpButton;
	CFSprite*	m_DownButton;

	s3eInputAdapter* inputAdapater;
	GestureManager* gestureManager;

	TapGesture*	m_DownTap;
	TapGesture*	m_UpTap;

public:
	GestureTest();
	~GestureTest();

	void OnUpTap(Event& evt);
	void OnDownTap(Event& evt);

	void Update(float deltaTime);
	void Render();
};

#endif


