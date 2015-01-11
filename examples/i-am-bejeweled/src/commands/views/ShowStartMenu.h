#ifndef _SHOWSTARTMENU_H_
#define _SHOWSTARTMENU_H_

#include <Command.h>

class ShowStartMenu : public Command
{
public:
	ShowStartMenu() {}
	~ShowStartMenu() {}

	void Execute() override;
};

#endif