#pragma once
#include "Macros.hpp"

C_EXTERN
{
	#include <cvar.h>
}

namespace Iswenzz::CoD4x
{
	class Debug
	{
	public:
		inline static cvar_t* PacketSize;

		/**
		 * @brief Initialize debug.
		 */
		static void Initialize();

		/**
		 * @brief Debug packet size.
		 * @param size - The packet size.
		 */
		static void NetchanPacketSize(int size);
	};
}
