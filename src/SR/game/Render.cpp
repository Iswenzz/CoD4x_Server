#include "Render.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	void Render::Frame() { }
}

C_EXTERN void SR_Frame()
{
	SR->Render->Frame();
}
