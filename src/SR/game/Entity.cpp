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

		int num = ent->s.number;
		if (num < 0 || num >= MAX_GENTITIES)
			return;

		SR->Entities[num] = std::make_shared<Entity>(ent);
	}
}
