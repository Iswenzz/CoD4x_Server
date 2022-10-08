#include "Player.hpp"
#include <sr.h>
#include <memory>

namespace Iswenzz::SR::CoD4x
{
	void PlayerCommands::Register()
	{
		Scr_AddMethod("surfaceflags", SurfaceFlags, qfalse);
		Scr_AddMethod("getviewheightlerpdown", GetViewHeightLerpDown, qfalse);
		Scr_AddMethod("getviewheightlerptarget", GetViewHeightLerpTarget, qfalse);
		Scr_AddMethod("getviewheightlerptime", GetViewHeightLerpTime, qfalse);
		Scr_AddMethod("getdamagetimer", GetDamageTimer, qfalse);
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
