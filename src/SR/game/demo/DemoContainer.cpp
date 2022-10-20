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

	void DemoContainer::RegisterSpeedrunDemo(const std::string &map,
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
			std::string id = mode + "-" + way;
			Demos.insert({ id, std::make_shared<Demo>(demos.at(0)) });

			Log::WriteLine("[DemoContainer] Register demo " + id);
			Log::WriteLine("[DemoContainer]  " + std::to_string(Demos.size()));
		}
	}
}
