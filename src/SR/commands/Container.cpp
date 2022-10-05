#include "Container.hpp"
#include "Player.hpp"

namespace Iswenzz::SR::CoD4x
{
	void CommandsContainer::Register()
	{
		Commands.push_back(std::make_unique<PlayerCommands>());
	}
}
