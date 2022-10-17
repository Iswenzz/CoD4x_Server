#include "Player.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	void PlayerCommands::Register()
	{
		Scr_AddMethod("surfaceflags", SurfaceFlags, qfalse);
		Scr_AddMethod("getviewheightlerpdown", GetViewHeightLerpDown, qfalse);
		Scr_AddMethod("getviewheightlerptarget", GetViewHeightLerpTarget, qfalse);
		Scr_AddMethod("getviewheightlerptime", GetViewHeightLerpTime, qfalse);
		Scr_AddMethod("getdamagetimer", GetDamageTimer, qfalse);
		Scr_AddMethod("playdemo", PlayDemo, qfalse);
	}

	void PlayerCommands::SurfaceFlags(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		Scr_AddInt(SR->Players[ent->client->ps.clientNum]->SurfaceFlags);
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

	void PlayerCommands::PlayDemo(scr_entref_t num)
	{
		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		std::string path = R"(D:\Vids\CoD4\izengine\mp_dr_darmuhv2.dm_1)";
		auto player = SR->Players[num.entnum];
		player->Demo->Open(path);
		Scr_AddEntity(player->Demo->Entity);
	}
}
