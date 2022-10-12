#pragma once
#include "Macros.hpp"

#include "game/Render.hpp"
#include "commands/Container.hpp"
#include "player/Player.hpp"

#include <array>
#include <memory>

namespace Iswenzz::CoD4x
{
	class Server
	{
	public:
		std::unique_ptr<Render> Render;
		std::array<std::shared_ptr<Player>, MAX_CLIENTS> Players{};

		/**
		 * @brief Server module initialization.
		 */
		Server();
		~Server();
	};
}

using namespace Iswenzz::CoD4x;
extern Server *SR;
