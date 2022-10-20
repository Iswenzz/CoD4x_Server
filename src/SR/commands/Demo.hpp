#pragma once
#include "Command.hpp"

namespace Iswenzz::CoD4x
{
	class DemoCommands : public Command
	{
	public:
		/// @brief Register commands.
		static void Register();

		/// @brief Register a speedrun demo.
		static void RegisterSpeedrunDemo();

		/// @brief Play a demo on a client.
		/// @param num - The client num.
		static void PlayDemo(scr_entref_t num);
	};
}
