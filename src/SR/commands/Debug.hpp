#pragma once
#include "Command.hpp"

namespace Iswenzz::CoD4x
{
	class DebugCommands : public Command
	{
	public:
		/// @brief Register commands.
		static void Register();

		/// @brief Debug test.
		static void Test();

		/// @brief Debug entity.
		static void Entity();

		/// @brief Debug breakpoint.
		static void Breakpoint();
	};
}
