#pragma once
#include "sr.hpp"

extern "C"
{
	#include <g_shared.h>
	#include <g_sv_shared.h>
}

namespace Iswenzz::SR::CoD4x
{
	class PMove
	{
	public:
		static void ExtendedInitForClient(client_t *cl);
		static void ExtendedResetState();
		static void ExtendedTurnOn();
		static int GetSpeed(playerState_t *ps);
		static float GetJumpHeight(unsigned int num);
		static void StuckInClient(gentity_t* gen);
	};
}
