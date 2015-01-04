#include "RenderSupport.h"

void RenderSupport::NextFrame()
{
	ResetMatrix();

	m_DrawCount = 0;
}

void RenderSupport::FinishQuadBatch()
{
	m_DrawCount++;
}

void RenderSupport::ResetMatrix()
{
}