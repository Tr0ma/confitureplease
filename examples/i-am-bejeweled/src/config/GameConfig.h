#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_

#include "ContextConfig.h"

class GameConfig : public ContextConfig
{
public:
	GameConfig() {}
	~GameConfig() {}

protected:
	void Configure() override;
};

#endif