#ifndef __SR_H__
#define __SR_H__

#include "q_shared.h"
#include "entity.h"
#include "player.h"
#include "sys_cod4defs.h"
#include "cvar.h"
#include "qcommon_io.h"

void SR_Init();

typedef struct {
	int 	fps;
	int 	frames;
	int 	playerMoveSpeed;
} client_sr_t;

typedef struct {
	client_sr_t 	clients[MAX_CLIENTS];
} sr_t;

extern sr_t sr;

#endif
