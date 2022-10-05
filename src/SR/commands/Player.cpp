#include "Player.hpp"
#include <sr.h>

namespace Iswenzz::SR::CoD4x
{
	PlayerCommands::PlayerCommands()
	{
		// auto a = std::function(SurfaceFlags);
		auto a = std::mem_fn(SurfaceFlags);
		struct std::_Mem_fn<void (Iswenzz::SR::CoD4x::PlayerCommands::*)(scr_entref_t num)> = a;
		// Method("surfaceflags", std::bind(SurfaceFlags), false);
		// Method("getviewheightlerpdown", GetViewHeightLerpDown, false);
		// Method("getviewheightlerptarget", GetViewHeightLerpTarget, false);
		// Method("getviewheightlerptime", GetViewHeightLerpTime, false);
		// Method("getdamagetimer", GetDamageTimer, false);
	}

	void PlayerCommands::SurfaceFlags(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(sr.clients[ent->client->ps.clientNum].surfaceFlags);
	}

	void PlayerCommands::GetViewHeightLerpDown(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(ent->client->ps.viewHeightLerpDown);
	}

	void PlayerCommands::GetViewHeightLerpTarget(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(ent->client->ps.viewHeightLerpTarget);
	}

	void PlayerCommands::GetViewHeightLerpTime(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(ent->client->ps.viewHeightLerpTime);
	}

	void PlayerCommands::GetDamageTimer(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(ent->client->ps.damageTimer);
	}
}
