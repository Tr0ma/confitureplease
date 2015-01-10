#ifndef _STARTUPAPPLICATION_H_
#define _STARTUPAPPLICATION_H_

#include "Command.h"

class StartupApplication : public Command
{
public:
	StartupApplication() {}
	~StartupApplication() {}

	virtual void Execute() override;
};

#endif