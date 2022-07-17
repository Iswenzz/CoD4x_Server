#include "sr.h"

sr_t sr;

/**
 * @brief
 * SR Initialization from Com_Init()
 */
void SR_Init()
{
    memset(&sr, 0, sizeof(sr));

	Scr_AddMethod("surfaceflags", PlayerCmd_SurfaceFlags, 0);
	Scr_AddMethod("getviewheightlerpdown", PlayerCmd_GetViewHeightLerpDown, 0);
	Scr_AddMethod("getviewheightlerptarget", PlayerCmd_GetViewHeightLerpTarget, 0);
	Scr_AddMethod("getviewheightlerptime", PlayerCmd_GetViewHeightLerpTime, 0);
	Scr_AddMethod("getdamagetimer", PlayerCmd_GetDamageTimer, 0);
}

void PlayerCmd_SurfaceFlags(scr_entref_t num)
{
	gentity_t *ent = VM_GetGEntityForNum(num);

	if (!ent || !ent->client)
	{
        Scr_ObjectError("not a client\n");
        return;
    }

	Scr_AddInt(sr.clients[ent->client->ps.clientNum].surfaceFlags);
}

void PlayerCmd_GetViewHeightLerpDown(scr_entref_t num)
{
	gentity_t *ent = VM_GetGEntityForNum(num);

	if (!ent || !ent->client)
	{
        Scr_ObjectError("not a client\n");
        return;
    }

	Scr_AddInt(ent->client->ps.viewHeightLerpDown);
}

void PlayerCmd_GetViewHeightLerpTarget(scr_entref_t num)
{
	gentity_t *ent = VM_GetGEntityForNum(num);

	if (!ent || !ent->client)
	{
        Scr_ObjectError("not a client\n");
        return;
    }

	Scr_AddInt(ent->client->ps.viewHeightLerpTarget);
}

void PlayerCmd_GetViewHeightLerpTime(scr_entref_t num)
{
	gentity_t *ent = VM_GetGEntityForNum(num);

	if (!ent || !ent->client)
	{
        Scr_ObjectError("not a client\n");
        return;
    }

	Scr_AddInt(ent->client->ps.viewHeightLerpTime);
}

void PlayerCmd_GetDamageTimer(scr_entref_t num)
{
	gentity_t *ent = VM_GetGEntityForNum(num);

	if (!ent || !ent->client)
	{
        Scr_ObjectError("not a client\n");
        return;
    }

	Scr_AddInt(ent->client->ps.damageTimer);
}
