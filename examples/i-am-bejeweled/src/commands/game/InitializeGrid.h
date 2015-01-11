#ifndef _INITIALIZEGRID_H_
#define _INITIALIZEGRID_H_

#include "Command.h"

class GemModel;
class GridModel;

class InitializeGrid : public Command
{
private:
	GridModel*	m_GridModel;
	GemModel*	m_GemModel;

public:
	InitializeGrid() {}
	~InitializeGrid() {}

protected:
	virtual void Execute() override;

private:
	bool IsHorizontalValid(const int colId, const int rowId, const char* selection);
	bool IsVerticalValid(const int colId, const int rowId, const char* selection);
};

#endif