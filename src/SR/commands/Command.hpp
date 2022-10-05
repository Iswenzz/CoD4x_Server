#pragma once
#include "sr.hpp"

#include <functional>
#include <string>

C_EXTERN
{
	#include <scr_vm.h>
}

namespace Iswenzz::SR::CoD4x
{
	/**
	 * @brief Command abstract class.
	 */
	class Command
	{
	public:
		bool Method(std::string name, std::function<void(const Command&, scr_entref_t)> method, bool developer);
	}
}
