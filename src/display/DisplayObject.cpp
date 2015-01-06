#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "MatrixUtil.h"
#include <math.h>

void DisplayObject::SetX(int value)
{
	if (m_X != value)
	{
		m_X = value;
		m_OrientationChanged = true;
	}
}

void DisplayObject::SetY(int value)
{
	if (m_Y != value)
	{
		m_Y = value;
		m_OrientationChanged = true;
	}
}

void DisplayObject::SetPivotX(int value)
{
	if (m_PivotX != value)
	{
		m_PivotX = value;
		m_OrientationChanged = true;
	}
}

void DisplayObject::SetPivotY(int value)
{
	if (m_PivotY != value)
	{
		m_PivotY = value;
		m_OrientationChanged = true;
	}
}

void DisplayObject::SetScaleX(float value)
{
	if (m_ScaleX != value)
	{
		m_ScaleX = value;
		m_OrientationChanged = true;
	}
}

void DisplayObject::SetScaleY(float value)
{
	if (m_ScaleY != value)
	{
		m_ScaleY = value;
		m_OrientationChanged = true;
	}
}

void DisplayObject::SetRotation(float value)
{
	// todo : normalize rotation

	if (m_Rotation != value)
	{
		m_Rotation = value;
		m_OrientationChanged = true;
	}
}

void DisplayObject::SetAlpha(float value)
{
	m_Alpha = value < 0 ? 0 : (value > 1.0f) ? 1.0f : value;
}

void DisplayObject::SetParent(DisplayObjectContainer* value)
{
	// todo check if we re not adding it to itself
	m_Parent = value;
}

DisplayObject& DisplayObject::GetBase()
{
	DisplayObject& current = *this;
	while(current.GetParent())
	{
		current = *dynamic_cast<DisplayObject*>(current.GetParent());
	}

	return current;
}

bool DisplayObject::hasVisibleArea()
{
	// add scaleX/scaleY != 0
	return m_Alpha != 0 && m_Visible;
}

Matrix& DisplayObject::GetTransformationMatrix()
{
	if (m_OrientationChanged)
	{
		m_OrientationChanged = false;

		if (m_Rotation == 0)
		{
			m_TransformationMatrix.SetTo(m_ScaleX, 0, 0, m_ScaleY, 
				m_X - m_PivotX * m_ScaleX, m_Y - m_PivotY * m_ScaleY);
		}
		else
		{
			float cosa = static_cast<float>(cos(m_Rotation));
			float sina = static_cast<float>(sin(m_Rotation));
			float a = m_ScaleX * cosa;
			float b = m_ScaleX * sina;
			float c = m_ScaleY * -sina;
			float d = m_ScaleY * cosa;
			float tx = m_X - m_PivotX * a - m_PivotY * c;
			float ty = m_Y - m_PivotY * b - m_PivotY * d;

			m_TransformationMatrix.SetTo(a, b, c , d, tx, ty);
		}
	}

	return m_TransformationMatrix;
}

Matrix&	DisplayObject::GetRelativeTransformationMatrix(DisplayObject* target, Matrix* resultMatrix)
{
	DisplayObject* commonParent = nullptr;
	DisplayObject* currentObject = nullptr;

	if (resultMatrix)
	{
		resultMatrix->Identity();
	}
	else
	{
		resultMatrix = new Matrix();
	}

	if (target == this)
	{
		return *resultMatrix;
	}
	else if (target == dynamic_cast<DisplayObject*>(m_Parent) || (!target && !m_Parent))
	{
		resultMatrix->CopyFrom(GetTransformationMatrix());
		return *resultMatrix;
	}
	else if (!target || target == &GetBase())
	{
		currentObject = this;
		while (currentObject != target)
		{
			MatrixUtil::PrependMatrix(*resultMatrix, currentObject->GetTransformationMatrix());
			currentObject = currentObject->m_Parent;
		}

		return *resultMatrix;
	}
	else if (target->GetParent() == this)
	{
		target->GetRelativeTransformationMatrix(this, resultMatrix);
	}



}
