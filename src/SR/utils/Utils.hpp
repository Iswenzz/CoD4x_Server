#pragma once
#include <string>
#include <vector>

#define HasFlag(var, flag) (var & flag) == flag

namespace Iswenzz::CoD4x
{
	/// @brief Utility class.
	class Utils
	{
	public:
		/// @brief Split a string from a delimiter.
		/// @param source - The string source.
		/// @param delimiter - The split delimiter.
		/// @return
		static std::vector<std::string> SplitString(const std::string& source, char delimiter);

		/// @brief Average mode a given vector.
		/// @tparam T - The elemements type.
		/// @param vec - The vector source.
		/// @return
		template <class T>
		static T VectorAverageMode(const std::vector<T>& vec)
		{
			const T* set = vec.data();
			T mode = set[0];

			int current = 0;
			int mostOccured = 0;

			for (int x = 0; x < vec.size(); x++)
			{
				if (set[x] == set[x + 1])
					current++;
				else
				{
					if (current > mostOccured)
					{
						mostOccured = current;
						mode = set[x];
					}
					current = 0;
				}
			}
			return mode;
		}
	};
}
