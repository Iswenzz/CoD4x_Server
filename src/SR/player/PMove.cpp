#include "PMove.hpp"
#include "Player.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	PMove::PMove(class Player *Player)
	{
		this->Player = Player;

		Player->Speed = g_speed ? g_speed->integer : 190;
		Player->ps->gravity = g_gravity ? (int)g_gravity->value : 800;
		Player->cl->jumpHeight = jump_height ? jump_height->value : 39;
	}

	void PMove::SetSpeed(int speed)
	{
		Player->Speed = speed;
	}

	int PMove::GetSpeed()
	{
		return Player->Speed;
	}

	float PMove::GetJumpHeight()
	{
		return Player->cl->jumpHeight;
	}

	void PMove::JumpUpdateSurface(pml_t *pml)
	{
		Player->SurfaceFlags = pml->groundTrace.sflags;
	}

	void PMove::StuckInClient() { }
}

C_EXTERN
{
	void Pmove_SetSpeed(unsigned int num, int speed)
	{
		SR->Players[num]->Speed = speed;
	}

	OPTIMIZE3 int Pmove_GetSpeed(playerState_t *ps)
	{
		return SR->Players[ps->clientNum]->Speed;
	}

	void Jump_UpdateSurface(playerState_s *ps, pml_t *pml)
	{
		SR->Players[ps->clientNum]->PMove->JumpUpdateSurface(pml);
	}

	float Dirty_GetJumpHeight(unsigned int num)
	{
		return SR->Players[num]->PMove->GetJumpHeight();
	}

	OPTIMIZE3 void StuckInClient(gentity_t* gen) { }
}
