#ifndef _RENDERSUPPORT_H_
#define _RENDERSUPPORT_H_

#include "Matrix.h"
#include "DisplayObject.h"
#include "Texture.h"
#include <vector>

using namespace std;

class Image;

class RenderSupport
{
private:
	vector<Matrix*>		m_MatrixStack;
	unsigned int		m_MatrixStackSize;
	Matrix				m_ModelViewMatrix;
	Texture*			m_CurrentTexture;
	int					m_DrawCount;

public:
	int GetDrawCount() { return m_DrawCount; }

public:
	RenderSupport() : m_MatrixStackSize(0), m_DrawCount(0), m_CurrentTexture(nullptr) {}
	~RenderSupport() {}

	void NextFrame();
	void PrependMatrix(Matrix& matrix);
	void TransformMatrix(DisplayObject& object);
	void PushMatrix();
	void PopMatrix();
	void DrawImage(Image& image, float parentAlpha);

private:
	void ResetMatrix();
};

#endif