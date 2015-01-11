#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_

#include "ContextConfig.h"
#include "Command.h"

class Confiture;

class GameConfig : public ContextConfig
{

private:
	Confiture* confiture;

public:
	GameConfig() {}
	~GameConfig() {}

protected:
	void Configure() override;
	void Dispose() override;

private:
	Command& GetStartUpApplication();
};

#endif