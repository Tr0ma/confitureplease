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
	Command& GetStartUpApplication();
	Command& GetShowStartMenu();

	View& GetStartMenuView();

	Mediator& GetStartMenuMediator();
};

#endif