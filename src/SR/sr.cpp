#include "sr.hpp"
#include "commands/Container.hpp"

using namespace Iswenzz::SR::CoD4x;

C_EXTERN void SR_Initialize()
{
	CommandsContainer::Register();
}

C_EXTERN void SR_Shutdown()
{

}
