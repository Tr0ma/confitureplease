#ifndef _MOVEGEMSDOWN_H_
#define _MOVEGEMSDOWN_H_

#include "Command.h"

class GemModel;
class GridModel;

class MoveGemsDown : public Command
{
private:
	GridModel*	m_GridModel;
	GemModel*	m_GemModel;

public:
	MoveGemsDown() {}
	~MoveGemsDown() {}

protected:
	virtual void Execute() override;
};

#endif