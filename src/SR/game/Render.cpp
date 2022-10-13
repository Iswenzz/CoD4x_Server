#include "Render.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	void Render::Frame()
	{
		for (const auto &player : SR->Players)
			player->Frame();
	}
}

C_EXTERN void SR_Frame()
{
	SR->Render->Frame();
}
