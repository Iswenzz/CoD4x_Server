#pragma once

namespace Iswenzz::CoD4x
{
	/// @brief Server render frame.
	class Render
	{
	public:
		/// @brief Construct a new Render object.
		Render() = default;
		~Render() = default;

		/// @brief The render frame.
		void Frame();
	};
}
