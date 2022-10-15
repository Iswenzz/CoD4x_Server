#pragma once
#include "Macros.hpp"
#include <CoD4DM1/API/DemoReader.hpp>
#include <memory>

namespace Iswenzz::CoD4x
{
	class Demo
	{
	public:
		std::unique_ptr<Iswenzz::CoD4::DM1::DemoReader> Reader;

		/**
		 * @brief Initialize a new Demo.
		 */
		Demo();
		~Demo();

		/**
		 * @brief Play the demo on a bot.
		 */
		void PlayDemo();
	};
}
