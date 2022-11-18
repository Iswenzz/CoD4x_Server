#include "Container.hpp"
#include "Debug.hpp"
#include "Demo.hpp"
#include "Entity.hpp"
#include "Player.hpp"

namespace Iswenzz::CoD4x
{
	void CommandsContainer::Register()
	{
		DebugCommands::Register();
		DemoCommands::Register();
		EntityCommands::Register();
		PlayerCommands::Register();
	}
}
