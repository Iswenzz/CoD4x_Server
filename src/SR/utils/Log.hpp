#pragma once
#include <iostream>
#include <string>

namespace Iswenzz::CoD4x
{
	/**
	 * @brief Log utility class.
	 */
	class Log
	{
	public:
		/**
		 * @brief Write a line to the console.
		 * @param message - The message.
		 */
		static void WriteLine(std::string message);

		/**
		 * @brief Write to the console
		 * @param message - The message.
		 */
		static void Write(std::string message);
	};
}
