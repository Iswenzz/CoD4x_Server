/*
===========================================================================
    Copyright (C) 2010-2013  Ninja and TheKelm

    This file is part of CoD4X18-Server source code.

    CoD4X18-Server source code is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    CoD4X18-Server source code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
===========================================================================
*/



#include "q_math.h"
#include "cvar.h"
#include "q_shared.h"
#include "g_shared.h"
#include "qcommon_io.h"
#include "entity.h"
#include "player.h"
#include "server.h"
#include "g_sv_shared.h"

#include <math.h>

qboolean extendedMovementControl = 0;

//This function init movement variables with default values
void Pmove_ExtendedInitForClient(client_t *cl)
{
    if (cl->gentity && cl->gentity->client)
    {
        if(g_gravity)
            cl->gentity->client->ps.gravity = (int)g_gravity->value;
        else
            cl->gentity->client->ps.gravity = 800;
    }

    if(g_speed)
        cl->playerMoveSpeed = g_speed->integer;
    else
        cl->playerMoveSpeed = 190;

    if(jump_height)
        cl->jumpHeight = jump_height->value;
    else
        cl->jumpHeight = 39;
}

void Pmove_ExtendedResetState(void)
{
    int i;
    client_t *cl;

    for(cl = svs.clients, i = 0; i < MAX_CLIENTS; i++)
        Pmove_ExtendedInitForClient(cl);

    extendedMovementControl = qfalse;
}

void Pmove_ExtendedTurnOn(void)
{
    int i;
    client_t *cl;

    if(extendedMovementControl)
        return;

    for(cl = svs.clients, i = 0; i < MAX_CLIENTS; i++)
        Pmove_ExtendedInitForClient(cl);

    extendedMovementControl = qtrue;
}

__cdecl __optimize3 int Pmove_GetSpeed(playerState_t *ps) 
{
	if(extendedMovementControl)
        return svs.clients[ps->clientNum].playerMoveSpeed;
	else
		return g_speed->integer;
}

float Dirty_GetJumpHeight(unsigned int num)
{
    if(extendedMovementControl)
		return level.clients[num].jumpHeight;
	else
		return jump_height->value;
}

__cdecl __optimize3 void StuckInClient(gentity_t* gen) { }
