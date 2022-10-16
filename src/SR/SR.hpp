#pragma once
#include "Macros.hpp"

#include "game/Debug.hpp"
#include "game/Server.hpp"
#include "net/Netchan.hpp"
#include "commands/Container.hpp"
#include "player/Player.hpp"
#include "utils/Log.hpp"

#include <array>
#include <memory>

namespace Iswenzz::CoD4x
{
	class Game
	{
	public:
		std::unique_ptr<Server> Server;
		std::unique_ptr<Netchan> Netchan;

		std::array<std::shared_ptr<Player>, MAX_CLIENTS> Players{};

		/// @brief Server module initialization.
		Game();
		~Game();
	};
}

using namespace Iswenzz::CoD4x;
extern Game *SR;
