#include "DisplayObjectContainer.h"
#include "RenderSupport.h"
#include "MatrixUtil.h"
#include <limits> 

using namespace std;

DisplayObject& DisplayObjectContainer::AddChild(DisplayObject& child)
{
	return AddChildAt(child, m_Children.size());
}

DisplayObject& DisplayObjectContainer::AddChildAt(DisplayObject& child, int index)
{
	m_NumChildren++;
	m_Children.insert(m_Children.begin() + index, &child);

	child.SetParent(this);
	return child;
}

DisplayObject& DisplayObjectContainer::RemoveChild(DisplayObject& child)
{
	return CleanChild(child, GetChildIndex(child));
}

DisplayObject& DisplayObjectContainer::RemoveChildAt(int index)
{
	return CleanChild(GetChildAt(index), index);
}

DisplayObject& DisplayObjectContainer::GetChildAt(int index)
{
	return *m_Children[index];
}

int	DisplayObjectContainer::GetChildIndex(DisplayObject& container)
{
	for (int i = 0 ; i < m_NumChildren ; i++)
	{
		if (m_Children[i] == &container)
		{
			return i;
		}
	}

	return -1;
}

Rectangle& DisplayObjectContainer::GetBounds(DisplayObject& target, Rectangle& resultRect)
{
	if (m_NumChildren == 0)
	{
		GetRelativeTransformationMatrix(&target, helperMatrix);
		MatrixUtil::TransformCoords(helperMatrix, 0.0f, 0.0f, helperVec2d);
		resultRect.SetTo(helperVec2d.x, helperVec2d.y, 0, 0);
	}
	else if (m_NumChildren == 1)
	{
		m_Children[0]->GetBounds(target, resultRect);
	}
	else
	{
		float minX = numeric_limits<float>::max();
		float minY = numeric_limits<float>::max();
		float maxX = numeric_limits<float>::min();
		float maxY = numeric_limits<float>::min(); 

		for (int i = 0 ; i < m_NumChildren ; i++)
		{
			m_Children[i]->GetBounds(target, resultRect);

			if (minX > resultRect.m_X) minX = resultRect.m_X;
			if (maxX < resultRect.GetRight()) maxX = resultRect.GetRight();
			if (minY > resultRect.m_Y) minY = resultRect.m_Y;
			if (maxY > resultRect.GetBottom()) maxY = resultRect.GetBottom();
		}

		resultRect.SetTo(minX, minY, maxX - minX, maxY - minY);
	}

	return resultRect;
}

DisplayObject* DisplayObjectContainer::HitTest(Vec2d localPoint)
{
    if (!GetVisible() || !GetTouchable()) return nullptr;

    float x = localPoint.x;
    float y = localPoint.y;
    DisplayObject* target = nullptr;

    for (int i = m_NumChildren - 1 ; i >=0 ; i--)
    {
        DisplayObject& child = *m_Children[i];
        GetRelativeTransformationMatrix(&child, helperMatrix);

        MatrixUtil::TransformCoords(helperMatrix, x, y, helperVec2d);
        target = child.HitTest(helperVec2d);

        if (target)
        {
            return target;
        }
    }

    return target;
}

void DisplayObjectContainer::Render(RenderSupport& renderSupport, float parentAlpha)
{
	float alpha = parentAlpha * GetAlpha();
	int numChildren = m_NumChildren;

	for (int i = 0 ; i < numChildren ; i++)
	{
		DisplayObject& child = *m_Children[i];
		if (child.hasVisibleArea())
		{
			renderSupport.PushMatrix();
			renderSupport.TransformMatrix(child);
			child.Render(renderSupport, parentAlpha);
			renderSupport.PopMatrix();
		}
	}

}

DisplayObject& DisplayObjectContainer::CleanChild(DisplayObject& child, int index)
{
	m_Children.erase(m_Children.begin() + index);
	m_NumChildren--;
	child.SetParent(nullptr);
	return child;
}
