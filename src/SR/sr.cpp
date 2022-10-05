#include "sr.hpp"
#include "commands/Container.hpp"

using namespace Iswenzz::SR::CoD4x;

CommandsContainer *commands;

C_EXTERN void SR_Initialize()
{
	commands = new CommandsContainer();
}

C_EXTERN void SR_Shutdown()
{
	delete commands;
}
