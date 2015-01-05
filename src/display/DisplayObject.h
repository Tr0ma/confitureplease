#ifndef _DISPLAYOBJECT_H_
#define _DISPLAYOBJECT_H_

#include "Matrix.h"

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

	DisplayObjectContainer*		GetParent() 								{ return m_Parent; }
	void						SetParent(DisplayObjectContainer* value);

public:
	DisplayObject() {}
	virtual ~DisplayObject() {}

	virtual void Render(RenderSupport& renderSupport, float parentAlpha) {}

	bool hasVisibleArea();

	Matrix& GetTransformationMatrix();
};

#endif