#include "RenderSupport.h"
#include "MatrixUtil.h"
#include "Image.h"
#include "Texture.h"
#include <Iw2D.h>
#include <cmath>

RenderSupport::~RenderSupport()
{
	m_MatrixStack.clear();
}

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
		/*Matrix* mat = m_MatrixPool.Get();
		mat->Identity();
		m_MatrixStack.push_back(mat);*/

		m_MatrixStack.push_back(new Matrix());
	}

	m_MatrixStack[m_MatrixStackSize++]->CopyFrom(m_ModelViewMatrix);
}

void RenderSupport::PopMatrix()
{
	int index = m_MatrixStackSize - 1;
	Matrix* matrix = m_MatrixStack[index];
	m_MatrixStack.erase(m_MatrixStack.begin() + index);
	m_ModelViewMatrix.CopyFrom(*(matrix));
	//m_MatrixPool.Release(matrix);

	delete matrix;

	m_MatrixStackSize--;
}

void RenderSupport::DrawImage(Image& image, float parentAlpha)
{
	if (!m_CurrentTexture || (&m_CurrentTexture->GetImage() != &image.GetTexture().GetImage()))
	{
		m_DrawCount++;
	}

	m_CurrentTexture = &image.GetTexture();

	Texture& texture = image.GetTexture();
	CIw2DImage* cIw2DImage = &(texture.GetImage());

	float x = image.GetX();
	float y = image.GetY();
	float w = texture.GetWidth();
	float h = texture.GetHeight();
	float srcX = texture.GetX();
	float srcY = texture.GetY();
	float srcW = texture.GetWidth();
	float srcH = texture.GetHeight();

	float a = m_ModelViewMatrix.m_A;
	float b = m_ModelViewMatrix.m_B;
	float c = m_ModelViewMatrix.m_C;
	float d = m_ModelViewMatrix.m_D;

	float tx = m_ModelViewMatrix.m_Tx;
	float ty = m_ModelViewMatrix.m_Ty;
	float sx = (a / abs(a)) * (sqrt(pow(a, 2.0f) + pow(c, 2.0f)));
	float sy = (d / abs(d)) * (sqrt(pow(b, 2.0f) + pow(d, 2.0f)));
	float q	= atan2(b, d); 

	Iw2DSetColour(0xffffffff);
	Iw2DSetTransformMatrix(CIwFMat2D::g_Identity);
	CIwFMat2D mat;
	mat.SetRot(q);
	mat.m[0][0] = sx;
	mat.m[1][1] = sy;
	mat.SetTrans(CIwFVec2(tx, ty));
	Iw2DSetTransformMatrix(mat);

	Iw2DDrawImageRegion(cIw2DImage, CIwFVec2(0, 0), CIwFVec2(w, h), CIwFVec2(srcX, srcY), CIwFVec2(srcW, srcH));
}

void RenderSupport::ResetMatrix()
{
	m_MatrixStackSize = 0;
	m_ModelViewMatrix.Identity();
}