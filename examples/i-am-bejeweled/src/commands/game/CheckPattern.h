#ifndef _CHECKPATTERN_H_
#define _CHECKPATTERN_H_

#include "Command.h"

class GemModel;
class GridModel;

class CheckPattern : public Command
{
private:
	GridModel*	m_GridModel;
	GemModel*	m_GemModel;

public:
	CheckPattern() {}
	~CheckPattern() {}

protected:
	virtual void Execute() override;
};

#endif