#include "Environment.hpp"

namespace Iswenzz::CoD4x
{
	void Environment::Build()
	{
		std::string modPath = fs_gameDirVar->string;
		modPath = modPath.replace(modPath.find("/"), 1, "\\");

		ModDirectory = std::filesystem::path(fs_basepath->string) / modPath;
	}
}
