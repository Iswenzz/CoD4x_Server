#pragma once
#include "Command.hpp"

namespace Iswenzz::CoD4x
{
	class EntityCommands : public Command
	{
	public:
		/// @brief Register commands.
		static void Register();

		/// @brief Play FX on tag.
		static void PlayFXOnTag();
	};
}
