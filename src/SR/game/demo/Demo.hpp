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
	};

	/// @brief Game demo.
	class Demo
	{
	public:
		std::unique_ptr<Iswenzz::CoD4::DM1::DemoReader> Reader;
		std::vector<DemoFrame> Frames;

		/// @brief Initialize a new Demo.
		/// @param path - The demo path.
		Demo(std::string path);
		~Demo();

		/// @brief Open a demo.
		void Open();
	};
}
