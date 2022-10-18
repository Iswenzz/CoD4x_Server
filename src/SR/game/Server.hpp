#pragma once
#include "game/Vegas.hpp"

C_EXTERN
{
	#include <sys_main.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Server container.
	class Server
	{
	public:
		std::unique_ptr<Vegas> Vegas;

		/// @brief Construct a new Server object.
		Server();
		~Server() = default;

		/// @brief Load the map.
		void LoadMap();

		/// @brief The server render frame.
		void Frame();
	};
}
