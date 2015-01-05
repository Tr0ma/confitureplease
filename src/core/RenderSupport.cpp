#include "RenderSupport.h"
#include "MatrixUtil.h"
#include "Image.h"

void RenderSupport::NextFrame()
{
	ResetMatrix();

	m_DrawCount = 0;
}

void RenderSupport::PrependMatrix(Matrix& matrix)
{
	MatrixUtil::PrependMatrix(m_ModelViewMatrix, matrix);
}

void RenderSupport::TransformMatrix(DisplayObject& object)
{
	MatrixUtil::PrependMatrix(m_ModelViewMatrix, object.GetTransformationMatrix());
}

void RenderSupport::PushMatrix()
{
	if (m_MatrixStack.size() < m_MatrixStackSize + 1)
	{
		m_MatrixStack.push_back(new Matrix());
	}

	m_MatrixStack[m_MatrixStackSize++]->CopyFrom(m_ModelViewMatrix);
}

void RenderSupport::PopMatrix()
{
	m_ModelViewMatrix.CopyFrom(*(m_MatrixStack[--m_MatrixStackSize]));
}

void RenderSupport::DrawImage(Image& image, float parentAlpha)
{
	if (&m_CurrentTexture->GetImage() != &image.GetTexture().GetImage())
	{
		m_DrawCount++;
	}

	// and now draw here
}

void RenderSupport::ResetMatrix()
{
	m_ModelViewMatrix.Identity();
}