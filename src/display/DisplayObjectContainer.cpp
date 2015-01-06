#include "DisplayObjectContainer.h"
#include "RenderSupport.h"

DisplayObject& DisplayObjectContainer::AddChild(DisplayObject& child)
{
	return AddChildAt(child, m_Children.size());
}

DisplayObject& DisplayObjectContainer::AddChildAt(DisplayObject& child, int index)
{
	m_NumChildren++;
	m_Children.insert(m_Children.begin() + index, &child);

	child.SetParent(this);
	//child.SetStage(m_Stage);

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

Rectangle DisplayObjectContainer::GetBounds()
{

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
