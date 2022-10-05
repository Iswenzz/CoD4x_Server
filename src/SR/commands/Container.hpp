#pragma once
#include "Command.hpp"

#include <memory>
#include <vector>

namespace Iswenzz::SR::CoD4x
{
	/**
	 * @brief Commands registration container.
	 */
	class CommandsContainer
	{
	public:
		/**
		 * @brief Register commands.
		 */
		void Register();

	private:
		std::vector<std::unique_ptr<Command>> Commands{};
	};
}
