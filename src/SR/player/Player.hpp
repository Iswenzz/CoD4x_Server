#pragma once
#include "PMove.hpp"
#include "game/Demo.hpp"
#include <vector>

C_EXTERN
{
	#include <server.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Player class.
	class Player
	{
	public:
		client_t* cl;
		playerState_t* ps;
		std::unique_ptr<PMove> pmove;
		std::unique_ptr<Demo> demo;

		int speed = 0;
		int surfaceFlags = 0;

		int currentFrameTime = 0;
		int previousFrameTime = 0;
		std::vector<int> frameTimes{ };

		/// @brief Initialize a new player.
		/// @param cl - The client.
		Player(client_t *cl);
		~Player() { }

		/// @brief Initialize the player.
		void Initialize();

		/// @brief Calculate the player FPS.
		void CalculateFPS();

		/// @brief Player packet.
		/// @param msg - The packet message.
		void Packet(msg_t *msg);

		/// @brief Player render frame.
		void Frame();

		/// @brief Get the last player frame.
		/// @return clientSnapshot_t*
		clientSnapshot_t *GetFrame();
	};
}
