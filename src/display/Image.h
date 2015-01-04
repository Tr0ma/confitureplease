#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "Iw2DSceneGraph.h"
#include "Updateable.h"
#include "Renderable.h"
#include <vector>

using namespace std;
using namespace Iw2DSceneGraph;
using namespace Iw2DSceneGraphCore;


class Stage;


class Container : public IUpdateable, public IRenderable
{
private:
	CNode* m_CNode;

protected:
	vector<Container*>	m_Children;
	Container*			m_Parent;
	Stage*				m_Stage;
	int					m_NumChildren;

public:
	virtual CNode&		GetCNode()						{ return *m_CNode; }

	Container*			GetParent()						{ return m_Parent; }
	void				SetParent(Container* value)		{ m_Parent = value; }

	Stage*				GetStage()						{ return m_Stage; }
	void				SetStage(Stage* value);

public:
	Container() : m_CNode(new CNode()), m_Parent(nullptr), m_Stage(nullptr), m_NumChildren(0) {}
	virtual ~Container() { delete m_CNode; }

	int			GetX() 								{ return static_cast<int>(GetCNode().m_X); }
	void		SetX(int value)						{ GetCNode().m_X = static_cast<float>(value); }

	int			GetY() 								{ return static_cast<int>(GetCNode().m_Y); }
	void		SetY(int value)						{ GetCNode().m_Y = static_cast<float>(value); }

	int			GetWidth() 							{ return static_cast<int>(GetCNode().m_W); }
	void		SetWidth(int value)					{ GetCNode().m_W = static_cast<float>(value); }

	int			GetHeight() 						{ return static_cast<int>(GetCNode().m_H); }
	void		SetHeight(int value) 				{ GetCNode().m_H = static_cast<float>(value); }

	float		GetRotation() 						{ return GetCNode().m_Angle; }
	void		SetRotation(float value) 			{ GetCNode().m_Angle = value; }

	float		GetScaleX() 						{ return GetCNode().m_ScaleX; }
	void		SetScaleX(float value) 				{ GetCNode().m_ScaleX = value; }

	float		GetScaleY() 						{ return GetCNode().m_ScaleY; }
	void		SetScaleY(float value) 				{ GetCNode().m_ScaleY = value; }

	float		GetAlpha() 							{ return GetCNode().m_Alpha; }
	void		SetAlpha(float value) 				{ GetCNode().m_Alpha = value; }

	bool		HitTest(int x, int y) 				{ return GetCNode().HitTest(x, y); }

	virtual Container&	AddChild(Container& child);
	virtual Container&	AddChildAt(Container& child, int index);
	virtual Container&	RemoveChild(Container& child);
	virtual Container&	RemoveChildAt(int index);
	Container&			GetChildAt(int index);
	int					GetChildIndex(Container& child);

	virtual void Update(float deltaTime = 0.0f) override;
	virtual void Render() override;

protected:
	virtual void Initialize() { m_CNode = new CNode(); }

private:
	Container& CleanChild(Container& child, int index);
};


class Sprite : public Container
{
private:
	CSprite*	m_CSprite;

public:
	Sprite() : m_CSprite(new CSprite()) {}
	virtual ~Sprite() { delete m_CSprite; }

	CNode&		GetCNode() override				{ return *m_CSprite; }
	void		SetImage(CIw2DImage* pImage)	{ (*m_CSprite).SetImage(pImage); }

protected:
	void		Initialize() override			{ m_CSprite = new CSprite(); }
};


class Stage : public Container
{
public:
	Stage() { m_Stage = this; }
	virtual ~Stage() {}

public:
	Container&	AddChild(Container& child) override;
	Container&	AddChildAt(Container& child, int index) override;
	Container&	RemoveChild(Container& child) override;
	Container&	RemoveChildAt(int index) override;

};

#endif