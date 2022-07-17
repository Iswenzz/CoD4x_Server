#pragma once

#include "cvar.h"
#include "entity.h"
#include "player.h"
#include "q_shared.h"
#include "qcommon_io.h"
#include "scr_vm.h"
#include "sys_cod4defs.h"

typedef struct
{
	int fps;
	int frames;
	int playerMoveSpeed;
	int surfaceFlags;
} sr_clients_t;

typedef struct
{
	sr_clients_t clients[MAX_CLIENTS];
} sr_t;

extern sr_t sr;

void SR_Init();
void PlayerCmd_SurfaceFlags(scr_entref_t num);
void PlayerCmd_GetViewHeightLerpDown(scr_entref_t num);
void PlayerCmd_GetViewHeightLerpTarget(scr_entref_t num);
void PlayerCmd_GetViewHeightLerpTime(scr_entref_t num);
void PlayerCmd_GetDamageTimer(scr_entref_t num);
