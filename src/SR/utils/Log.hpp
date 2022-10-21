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
		/// @brief Write a line to the console.
		/// @param fmt - The format.
		/// @param ... - Format arguments.
		static void WriteLine(const char *fmt, ...);

		/// @brief Write to the console.
		/// @param fmt - The format.
		/// @param ... - Format arguments.
		static void Write(const char *fmt, ...);
	};
}
