#ifndef _DISPLAYOBJECT_H_
#define _DISPLAYOBJECT_H_

#include "Matrix.h"
#include "Rectangle.h"
#include "Vec2d.h"

#include <vector>

using namespace std;

class RenderSupport;
class DisplayObjectContainer;

class DisplayObject
{
private:
	int							m_X;
	int							m_Y;
	int							m_PivotX;
	int							m_PivotY;
	float						m_ScaleX;
	float						m_ScaleY;
	float						m_Rotation;
	float						m_Alpha;
	bool						m_Visible;
	DisplayObjectContainer*		m_Parent;
	Matrix						m_TransformationMatrix;
	bool						m_OrientationChanged;

public:
	int			GetX() 							{ return m_X; }
	void		SetX(int value);

	int			GetY() 							{ return m_Y; }
	void		SetY(int value);

	int			GetPivotX()						{ return m_Y; }
	void		SetPivotX(int value);

	int			GetPivotY()						{ return m_Y; }
	void		SetPivotY(int value);

	float		GetScaleX()						{ return m_ScaleX; }
	void		SetScaleX(float value);

	float		GetScaleY()						{ return m_ScaleY; }
	void		SetScaleY(float value);

	float		GetRotation()					{ return m_Rotation; }
	void		SetRotation(float value);

	float		GetAlpha() 						{ return m_Alpha; }
	void		SetAlpha(float value);

	bool		GetVisible() 					{ return m_Visible; }
	void		SetVisible(bool value) 			{ m_Visible = value; }

	int			GetWidth();
	void		SetWidth(int value);

	int			GetHeight();
	void		SetHeight(int value);

	DisplayObjectContainer*		GetParent() 								{ return m_Parent; }
	void						SetParent(DisplayObjectContainer* value);

	DisplayObject&				GetBase();

protected:
	static vector<DisplayObject*>	ancestors;
	static Rectangle				helperRect;
	static Matrix					helperMatrix;
	static Vec2d					helperVec2d;

public:
	DisplayObject() 
		: m_X(0), m_Y(0), m_PivotX(0), m_PivotY(0), m_ScaleX(1.0f), m_ScaleY(1.0f), m_Rotation(0), 
		m_Alpha(1.0f), m_Visible(true), m_Parent(nullptr), m_OrientationChanged(false) {}

	virtual ~DisplayObject() {}

	bool				hasVisibleArea();
	virtual Rectangle&	GetBounds(DisplayObject& target, Rectangle& resultRect) { return resultRect; };
	Matrix&				GetTransformationMatrix();
	Matrix&				GetRelativeTransformationMatrix(DisplayObject* target, Matrix& resultMatrix);

	virtual void Render(RenderSupport& renderSupport, float parentAlpha) {}

private:
	DisplayObject*	FindCommonParent(DisplayObject& objectA, DisplayObject& objectB);
	int				GetIndexOf(vector<DisplayObject*> list, DisplayObject& target);
};

#endif