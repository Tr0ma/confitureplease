#ifndef _RENDERSUPPORT_H_
#define _RENDERSUPPORT_H_

class RenderSupport
{
private:
	int m_DrawCount;

public:
	int GetDrawCount() { return m_DrawCount; }

public:
	RenderSupport() : m_DrawCount(0) {}
	~RenderSupport() {}

	void NextFrame();
	void FinishQuadBatch();

private:
	void ResetMatrix();

};

#endif