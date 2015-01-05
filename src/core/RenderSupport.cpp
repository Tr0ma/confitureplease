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

	/*Iw2DSetTransformMatrix(CIwFMat2D::g_Identity);

	CIwFMat2D mat;
	mat.SetTrans()
	Iw2DSetTransformMatrix(mat);*/

	Texture& texture = image.GetTexture();
	CIw2DImage* cIw2DImage = &(texture.GetImage());
	int x = image.GetX();
	int y = image.GetY();
	int w = texture.GetWidth();
	int h = texture.GetHeight();
	int srcX = texture.GetX();
	int srcY = texture.GetY();
	int srcW = texture.GetWidth();
	int srcH = texture.GetHeight();

	Iw2DDrawImageRegion(cIw2DImage, CIwFVec2(x, y), CIwFVec2(w, h), CIwFVec2(srcX, srcY), CIwFVec2(srcW, srcH));
	// and now draw here
}

void RenderSupport::ResetMatrix()
{
	m_MatrixStackSize = 0;
	m_ModelViewMatrix.Identity();
}