#pragma once
#include "game/Vegas.hpp"
#include "game/Demo.hpp"

namespace Iswenzz::CoD4x
{
	/// @brief Server container.
	class Server
	{
	public:
		std::unique_ptr<Vegas> Vegas;
		std::unique_ptr<Demo> Demo;

		/// @brief Construct a new Server object.
		Server();
		~Server() = default;

		/// @brief Load the map.
		void LoadMap();

		/// @brief The server render frame.
		void Frame();
	};
}
