#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_

#include "ContextConfig.h"

class Command;
class Mediator;
class View;

class GameConfig : public ContextConfig
{
public:
	GameConfig() {}
	~GameConfig() {}

protected:
	void Configure() override;
	void Dispose() override;

private:
	Command&	GetStartUpApplication();
	Command&	GetShowStartMenu();
	Command&	GetShowGame();
	Command&	GetInitializeGrid();
	Command&	GetSwapAndCheck();
	Command&	GetMoveGemsDown();
	Command&	GetCheckPatterns();

	View&		GetStartMenuView();
	View&		GetGridView();

	Mediator&	GetStartMenuMediator();
	Mediator&	GetGridMediator();
};

#endif