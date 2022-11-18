#pragma once
#include "Macros.hpp"

C_EXTERN
{
	#include <entity.h>
}

namespace Iswenzz::CoD4x
{
	/// @brief Entity class.
	class Entity
	{
	public:
		gentity_t *g;

		bool HasFxOnTag = false;

		/// @brief Initialize a new Entity.
		/// @param ent - The entity.
		Entity(gentity_t *ent);
		~Entity() = default;
	};
}
