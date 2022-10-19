#pragma once
#include "Macros.hpp"

#include <CoD4DM1/API/DemoReader.hpp>
#include <CoD4DM1/Crypt/Huffman.hpp>
#include <memory>

C_EXTERN
{
	#include <scr_vm.h>
	#include <q_math.h>
}

namespace Iswenzz::CoD4x
{
	class Player;

	struct DemoFrame
	{
		playerState_t ps;
		int time;
		int fps;
		std::string playerName;
	};

	/// @brief Game demo.
	class Demo
	{
	public:
		Player *Player;
		gentity_t *Entity;

		std::unique_ptr<Iswenzz::CoD4::DM1::DemoReader> Reader;
		std::vector<DemoFrame> Frames;
		int FrameIndex = 0;
		int StartTime = 0;

		/// @brief Initialize a new Demo.
		Demo(class Player *player);
		~Demo();

		/// @brief Open a demo.
		/// @param path - The demo path.
		void Open(std::string path);

		/// @brief Get the current demo frame.
		/// @return
		DemoFrame GetFrame();

		/// @brief Demo render frame.
		void Frame();

		/// @brief Demo player frame.
		void PlayerFrame();
	};
}
