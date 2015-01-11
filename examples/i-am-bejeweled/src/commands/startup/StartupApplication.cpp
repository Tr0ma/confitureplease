#include "StartupApplication.h"
#include "ShowStartMenuEvent.h"

void StartupApplication::Execute()
{
	const ShowStartMenuEvent evt;
	GetDispatcher().Dispatch(evt);
}