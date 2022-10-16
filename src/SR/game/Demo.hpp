#pragma once
#include "Macros.hpp"

#include <CoD4DM1/API/DemoReader.hpp>
#include <CoD4DM1/Crypt/Huffman.hpp>
#include <memory>

C_EXTERN
{
	#include <scr_vm.h>
}

namespace Iswenzz::CoD4x
{
	class Player;

	/// @brief Game demo.
	class Demo
	{
	public:
		std::unique_ptr<Iswenzz::CoD4::DM1::DemoReader> Reader;
		int StartTime = 0;

		/// @brief Initialize a new Demo.
		Demo() = default;
		~Demo();

		/// @brief Demo render frame.
		/// @param player - The player.
		void Frame(Player *player);

		/// @brief Demo player frame.
		/// @param player - The player.
		void PlayerFrame(Player* player);
	};
}
