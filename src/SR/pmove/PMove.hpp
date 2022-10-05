#pragma once
#include "sr.hpp"

C_EXTERN
{
	#include <g_shared.h>
	#include <g_sv_shared.h>
	#include <bg_public.h>
}

namespace Iswenzz::SR::CoD4x
{
	/**
	 * @brief Player movement.
	 */
	class PMove
	{
	public:
		/**
		 * @brief Enable extended movement behavior.
		 * @param cl - The client.
		 */
		static void ExtendedInitForClient(client_t *cl);

		/**
		 * @brief Reset the extended movement.
		 */
		static void ExtendedResetState();

		/**
		 * @brief Turn on extended movement.
		 */
		static void ExtendedTurnOn();

		/**
		 * @brief Get the player speed.
		 * @param ps - The player speed.
		 */
		static int GetSpeed(playerState_t *ps);

		/**
		 * @brief Get the player jump height.
		 * @param num - The client number.
		 */
		static float GetJumpHeight(unsigned int num);

		/**
		 * @brief Update the player surface type on jump.
		 * @param ps - The player state.
		 * @param pml - The player movement.
		 */
		static void JumpUpdateSurface(playerState_s *ps, pml_t *pml);

		/**
		 * @brief Entity stuck in client.
		 * @param gen - The gentity.
		 */
		static void StuckInClient(gentity_t* gen);
	};
}
