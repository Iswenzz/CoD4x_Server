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

		/// @brief Check if a demo is playing on a client.
		/// @param num - The client num.
		static void IsDemoPlaying(scr_entref_t num);

		/// @brief Get the speedrun velocity.
		/// @param num - The client num.
		static void GetSpeedrunVelocity(scr_entref_t num);

		/// @brief Get the demo weapon.
		/// @param num - The client num.
		static void GetDemoWeapon(scr_entref_t num);

		/// @brief Stop a demo on a client.
		/// @param num - The client num.
		static void StopDemo(scr_entref_t num);
	};
}
