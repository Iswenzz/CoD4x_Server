#include "Demo.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	void DemoCommands::Register()
	{
		Scr_AddFunction("registerspeedrundemo", RegisterSpeedrunDemo, qfalse);
		Scr_AddMethod("playdemo", PlayDemo, qfalse);
	}

	void DemoCommands::RegisterSpeedrunDemo()
	{
		CHECK_PARAMS(5, "Usage: RegisterSpeedrunDemo(<map>, <playerId>, <runId>, <mode>, <way>)");

		std::string map = Scr_GetString(0);
		std::string playerId = Scr_GetString(1);
		std::string runId = Scr_GetString(2);
		std::string mode = Scr_GetString(3);
		std::string way = Scr_GetString(4);

		SR->DemoContainer->RegisterSpeedrunDemo(map, playerId, runId, mode, way);
	}

	void DemoCommands::PlayDemo(scr_entref_t num)
	{
		CHECK_PARAMS(2, "Usage: PlayDemo(<mode>, <way>)");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		std::string mode = Scr_GetString(0);
		std::string way = Scr_GetString(1);

		auto player = SR->Players[num.entnum];

		Log::WriteLine("[Debug] %d", SR->DemoContainer->Demos.size());

		auto demo = std::find_if(SR->DemoContainer->Demos.cbegin(), SR->DemoContainer->Demos.cend(),
			[&](const std::shared_ptr<Demo> &item) { return item->ID == mode + "-" + way; });

		if (demo != std::end(SR->DemoContainer->Demos))
		{
			Log::WriteLine("[DemoPlayer] Playing demo %p", (*demo).get());

			player->DemoPlayer->Play(*demo);
			Scr_AddEntity(player->DemoPlayer->Entity);
		}
	}
}
