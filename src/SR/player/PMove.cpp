#include "PMove.hpp"
#include "Player.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	PMove::PMove(std::shared_ptr<Player> player)
	{
		this->player = player;

		player->ps->gravity = g_gravity ? (int)g_gravity->value : 800;
		player->speed = g_speed ? g_speed->integer : 190;
		player->cl->jumpHeight = jump_height ? jump_height->value : 39;
	}

	void PMove::SetSpeed(int speed)
	{
		player->speed = speed;
	}

	int PMove::GetSpeed()
	{
		return player->speed;
	}

	float PMove::GetJumpHeight()
	{
		return player->cl->jumpHeight;
	}

	void PMove::JumpUpdateSurface(pml_t *pml)
	{
		player->surfaceFlags = pml->groundTrace.sflags;
	}

	void PMove::StuckInClient() { }
}

using namespace Iswenzz::CoD4x;

C_EXTERN void Pmove_SetSpeed(unsigned int num, int speed)
{
	SR->Players[num]->speed = speed;
}

C_EXTERN OPTIMIZE3 int Pmove_GetSpeed(playerState_t *ps)
{
	return SR->Players[ps->clientNum]->speed;
}

C_EXTERN void Jump_UpdateSurface(playerState_s *ps, pml_t *pml)
{
	// SR->Players[ps->clientNum]->pmove->JumpUpdateSurface(pml);
}

C_EXTERN float Dirty_GetJumpHeight(unsigned int num)
{
	// return SR->Players[num]->pmove->GetJumpHeight();
	return 39;
}

C_EXTERN OPTIMIZE3 void StuckInClient(gentity_t* gen) { }
