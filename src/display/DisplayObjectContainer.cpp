#include "DisplayObjectContainer.h"
#include "RenderSupport.h"

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