#ifndef _SWAPANDCHECK_H_
#define _SWAPANDCHECK_H_

#include "Command.h"

class GemModel;
class GridModel;

class SwapAndCheck : public Command
{
private:
	GridModel*	m_GridModel;
	GemModel*	m_GemModel;

public:
	SwapAndCheck() {}
	~SwapAndCheck() {}

protected:
	virtual void Execute() override;
};

#endif