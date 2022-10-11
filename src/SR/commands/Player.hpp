#pragma once
#include "Command.hpp"

namespace Iswenzz::CoD4x
{
	class PlayerCommands : public Command
	{
	public:
		/**
		 * @brief Register commands.
		 */
		static void Register();

		/**
		 * @brief Get the player surface flag.
		 */
		static void SurfaceFlags(scr_entref_t num);

		/**
		 * @brief Get the view height lerp down value.
		 */
		static void GetViewHeightLerpDown(scr_entref_t num);

		/**
		 * @brief Get the view height lerp target.
		 */
		static void GetViewHeightLerpTarget(scr_entref_t num);

		/**
		 * @brief Get the view height lerp time.
		 */
		static void GetViewHeightLerpTime(scr_entref_t num);

		/**
		 * @brief Get the damage timer.
		 */
		static void GetDamageTimer(scr_entref_t num);
	};
}
