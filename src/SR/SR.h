#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../g_sv_shared.h"

void SR_Initialize();
void SR_Shutdown();
void SR_SpawnServer(const char *levelname);
void SR_InitializePlayer(client_t *cl);
void SR_FreePlayer(client_t *cl);

void SR_Frame();
void SR_Packet(netadr_t *from, client_t* cl, msg_t *msg);

qboolean SR_DemoIsPlaying(client_t *cl);
void SR_DemoButton(client_t *cl, usercmd_t *cmd);
void SR_DemoUpdateEntity(client_t *cl, snapshotInfo_t *snapInfo, msg_t* msg, const int time, entityState_t* from, entityState_t* to, qboolean force);

#ifdef __cplusplus
}
#endif
