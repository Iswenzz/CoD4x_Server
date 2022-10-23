#include "DemoContainer.hpp"
#include "utils/Log.hpp"

#include <filesystem>

namespace Iswenzz::CoD4x
{
	DemoContainer::DemoContainer()
	{
		RegisterDemoFolder(R"(L:\migration\output)");
	}

	void DemoContainer::RegisterDemoFolder(const std::string &path)
	{
		Directories.push_back(path);
	}

	qboolean DemoContainer::RegisterSpeedrunDemo(const std::string &map,
		const std::string &playerId, const std::string &run, const std::string &mode, const std::string &way)
	{
		std::vector<std::string> demos{ };
		for (const std::string& folder : Directories)
		{
			auto demoDirectory = std::filesystem::path(folder) / playerId / map;
			if (!std::filesystem::exists(demoDirectory))
				continue;

			for (const auto& entry : std::filesystem::directory_iterator(demoDirectory.string()))
			{
				const std::string& entryName = entry.path().filename().string();
				if (entryName == run + ".dm_1" || entryName.find(run + "_") != std::string::npos)
					demos.push_back(entry.path().string());
			}
		}
		if (demos.size())
		{
			std::string id = fmt("times_%s_%s", mode.c_str(), way.c_str());
			Demos.push_back(std::make_shared<Demo>(id, demos.at(0)));

			Log::WriteLine("[DemoContainer] Register demo %s %s %s", id.c_str(), playerId.c_str(), run.c_str());
		}
		return static_cast<qboolean>(demos.size());
	}
}
