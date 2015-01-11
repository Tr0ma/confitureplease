#ifndef _SHOWGAMEMENU_H_
#define _SHOWGAMEMENU_H_

#include <Command.h>

class ShowGame : public Command
{
public:
	ShowGame() {}
	~ShowGame() {}

	void Execute() override;
};

#endif