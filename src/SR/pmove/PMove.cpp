#include "PMove.hpp"
#include <sr.h>

C_VARIABLE(qboolean extendedMovementControl = qfalse);

namespace Iswenzz::SR::CoD4x
{
	void PMove::ExtendedInitForClient(client_t *cl)
	{
		if (!cl->gentity || !cl->gentity->client)
			return;

		cl->gentity->client->ps.gravity = g_gravity ? (int)g_gravity->value : 800;
		sr.clients[cl->gentity->client->ps.clientNum].playerMoveSpeed = g_speed ? g_speed->integer : 190;
		cl->jumpHeight = jump_height ? jump_height->value : 39;
	}

	void PMove::ExtendedResetState()
	{
		int i;
		client_t *cl;

		for (cl = svs.clients, i = 0; i < MAX_CLIENTS; i++)
			Pmove_ExtendedInitForClient(cl);

		extendedMovementControl = qfalse;
	}

	void PMove::ExtendedTurnOn()
	{
		int i;
		client_t *cl;

		if (extendedMovementControl)
			return;

		for (cl = svs.clients, i = 0; i < MAX_CLIENTS; i++)
			Pmove_ExtendedInitForClient(cl);

		extendedMovementControl = qtrue;
	}

	int PMove::GetSpeed(playerState_t *ps)
	{
		return extendedMovementControl ? sr.clients[ps->clientNum].playerMoveSpeed : g_speed->integer;
	}

	float PMove::GetJumpHeight(unsigned int num)
	{
		return extendedMovementControl ? svs.clients[num].jumpHeight : jump_height->value;
	}

	void PMove::JumpUpdateSurface(playerState_s *ps, pml_t *pml)
	{
		sr.clients[ps->clientNum].surfaceFlags = pml->groundTrace.sflags;
	}

	void PMove::StuckInClient(gentity_t* gen) { }
}

using namespace Iswenzz::SR::CoD4x;

C_WRAPPER(PMove::ExtendedInitForClient, void Pmove_ExtendedInitForClient(client_t *cl), (cl));
C_WRAPPER(PMove::ExtendedResetState, void Pmove_ExtendedResetState(), ());
C_WRAPPER(PMove::ExtendedTurnOn, void Pmove_ExtendedTurnOn(), ());
C_WRAPPER(PMove::GetSpeed, OPTIMIZE3 int Pmove_GetSpeed(playerState_t *ps), (ps));
C_WRAPPER(PMove::GetJumpHeight, float Dirty_GetJumpHeight(unsigned int num), (num));
C_WRAPPER(PMove::JumpUpdateSurface, void Jump_UpdateSurface(playerState_s *ps, pml_t *pml), (ps, pml));
C_WRAPPER(PMove::StuckInClient, OPTIMIZE3 void StuckInClient(gentity_t* gen), (gen));
