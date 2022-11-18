#include "Entity.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Entity::Entity(gentity_t *ent)
	{
		g = ent;
	}
}

C_EXTERN
{
	void SR_InitializeEntity(gentity_t *ent)
	{
		if (!ent) return;

		SR->Entities[ent->s.number] = std::make_shared<Entity>(ent);
	}
}
