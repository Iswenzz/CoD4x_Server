#pragma once
#include "Macros.hpp"

#include <iostream>
#include <string>

C_EXTERN
{
	#include <q_shared.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Log utility class.
	class Log
	{
	public:
		/// @brief Print a message.
		/// @param channel - The channel.
		/// @param msg - The message.
		static void Print(conChannel_t channel, std::string msg);

		/// @brief Write a line to the console.
		/// @param fmt - The format.
		/// @param ... - Format arguments.
		static void WriteLine(std::string fmt, ...);

		/// @brief Write to the console.
		/// @param fmt - The format.
		/// @param ... - Format arguments.
		static void Write(std::string fmt, ...);
	};
}
