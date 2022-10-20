#include "Container.hpp"
#include "Player.hpp"
#include "Demo.hpp"

namespace Iswenzz::CoD4x
{
	void CommandsContainer::Register()
	{
		DemoCommands::Register();
		PlayerCommands::Register();
	}
}
