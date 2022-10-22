#pragma once
#include "Demo.hpp"

namespace Iswenzz::CoD4x
{
	class Player;

	/// @brief Play a demo on a player.
	class DemoPlayer
	{
	public:
		std::shared_ptr<Demo> Demo;

		Player *Player;
		gentity_t *Entity;
		int FrameIndex = 0;
		int StartTime = 0;

		/// @brief Initialize the DemoPlayer.
		/// @param player - The player.
		DemoPlayer(class Player *player);
		~DemoPlayer() = default;

		/// @brief Play a demo on a player.
		/// @param demo - The demo.
		void Play(const std::shared_ptr<class Demo>& demo);

		/// @brief Stop the demo.
		void Stop();

		/// @brief Get the current demo frame.
		/// @return
		DemoFrame GetFrame();

		/// @brief Demo player frame.
		void Frame();
	};
}
