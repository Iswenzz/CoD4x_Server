#pragma once
#include "Macros.hpp"
#include <memory>

C_EXTERN
{
	#include <g_shared.h>
	#include <g_sv_shared.h>
	#include <bg_public.h>
}

namespace Iswenzz::CoD4x
{
	class Player;

	/// @brief Player movement.
	class PMove
	{
	public:
		Player *player;

		/// @brief Initialier a new PMove.
		/// @param player - The player.
		PMove(Player *player);
		virtual ~PMove() = default;

		/// @brief Set the player speed.
		/// @param speed - The speed.
		void SetSpeed(int speed);

		/// @brief Get the player speed.
		int GetSpeed();

		/// @brief Get the player jump height.
		float GetJumpHeight();

		/// @brief Update the player surface type on jump.
		/// @param pml - The player movement.
		void JumpUpdateSurface(pml_t *pml);

		/// @brief Entity stuck in client.
		void StuckInClient();
	};
}
