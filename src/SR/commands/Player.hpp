#pragma once
#include "Command.hpp"

namespace Iswenzz::SR::CoD4x
{
	class PlayerCommands : public Command
	{
	public:
		PlayerCommands();
		virtual ~PlayerCommands() = default;

		void SurfaceFlags(scr_entref_t num);
		void GetViewHeightLerpDown(scr_entref_t num);
		void GetViewHeightLerpTarget(scr_entref_t num);
		void GetViewHeightLerpTime(scr_entref_t num);
		void GetDamageTimer(scr_entref_t num);
	};
}
