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
	struct DemoFrame
	{
		playerState_t ps;
		int time;
		int fps;
		std::string playerName;
		std::vector<std::string> chat;
	};

	/// @brief Game demo.
	class Demo
	{
	public:
		std::string ID;
		std::unique_ptr<Iswenzz::CoD4::DM1::DemoReader> Reader;
		std::vector<DemoFrame> Frames{ };
		std::array<std::string, MAX_CONFIGSTRINGS + 1> ConfigStrings{ };
		std::vector<std::string> Weapons{ };

		/// @brief Initialize a new Demo.
		/// @param id - The demo id.
		/// @param path - The demo path.
		Demo(std::string id, std::string path);
		~Demo();

		/// @brief Open a demo.
		void Open();

		/// @brief Process chat messages.
		/// @return
		std::vector<std::string> ProcessChat();
	};
}
