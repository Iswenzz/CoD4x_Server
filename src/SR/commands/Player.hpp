#pragma once
#include "Command.hpp"

namespace Iswenzz::SR::CoD4x
{
	class PlayerCommands : public Command
	{
	public:
		static void Register();
		static void SurfaceFlags(scr_entref_t num);
		static void GetViewHeightLerpDown(scr_entref_t num);
		static void GetViewHeightLerpTarget(scr_entref_t num);
		static void GetViewHeightLerpTime(scr_entref_t num);
		static void GetDamageTimer(scr_entref_t num);
	};
}
