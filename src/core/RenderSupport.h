#ifndef _RENDERSUPPORT_H_
#define _RENDERSUPPORT_H_

#include "Matrix.h"
#include "DisplayObject.h"
#include <vector>

using namespace std;

class RenderSupport
{
private:
	vector<Matrix*>		m_MatrixStack;
	int					m_MatrixStackSize;
	Matrix				m_ModelViewMatrix;

	int m_DrawCount;

public:
	int GetDrawCount() { return m_DrawCount; }

public:
	RenderSupport() : m_DrawCount(0) {}
	~RenderSupport() {}

	void NextFrame();
	void FinishQuadBatch();
	void PrependMatrix(Matrix& matrix);
	void TransformMatrix(DisplayObject& object);
	void PushMatrix();
	void PopMatrix();

private:
	void ResetMatrix();
};

#endif