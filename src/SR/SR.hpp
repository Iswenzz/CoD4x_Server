#pragma once
#include "Macros.hpp"

#include "game/Debug.hpp"
#include "game/Render.hpp"
#include "game/Vegas.hpp"
#include "game/Demo.hpp"
#include "net/Netchan.hpp"
#include "commands/Container.hpp"
#include "player/Player.hpp"
#include "utils/Log.hpp"

#include <array>
#include <memory>

namespace Iswenzz::CoD4x
{
	class Server
	{
	public:
		std::unique_ptr<Netchan> Netchan;
		std::unique_ptr<Render> Render;

		std::array<std::shared_ptr<Player>, MAX_CLIENTS> Players{};

		std::unique_ptr<Vegas> Vegas;
		std::unique_ptr<Demo> Speedrun;

		/// @brief Server module initialization.
		Server();
		~Server();
	};
}

using namespace Iswenzz::CoD4x;
extern Server *SR;
