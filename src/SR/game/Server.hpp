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

		/// @brief System sleep.
		/// @param ms - Milliseconds.
		void Sleep(int ms = 0);

		/// @brief Wait for a server frame to goes by.
		/// @param amount - The amount of frames to wait.
		void WaitFrame(int amount = 1);
	};
}
