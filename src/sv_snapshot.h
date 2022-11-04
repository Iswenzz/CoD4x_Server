#ifndef _SV_SNAPSHOT_H_
#define _SV_SNAPSHOT_H_
#include "player.h"

int SV_GetArchivedClientInfo(int clientNum, int *pArchiveTime, playerState_t *ps, clientState_t *cs, float *origin, int *health, int *otherFlags);

qboolean SR_DemoIsPlaying(client_t *cl);
void SR_DemoUpdateEntity(client_t *cl, snapshotInfo_t *snapInfo, msg_t* msg, const int time, entityState_t* from, entityState_t* to, qboolean force);

#endif