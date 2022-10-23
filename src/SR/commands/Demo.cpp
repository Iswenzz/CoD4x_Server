#include "Demo.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	void DemoCommands::Register()
	{
		Scr_AddFunction("registerspeedrundemo", RegisterSpeedrunDemo, qfalse);
		Scr_AddMethod("playdemo", PlayDemo, qfalse);
		Scr_AddMethod("isdemoplaying", IsDemoPlaying, qfalse);
		Scr_AddMethod("getspeedrunvelocity", GetSpeedrunVelocity, qfalse);
		Scr_AddMethod("getdemoweapon", GetDemoWeapon, qfalse);
		Scr_AddMethod("stopdemo", StopDemo, qfalse);
	}

	void DemoCommands::RegisterSpeedrunDemo()
	{
		CHECK_PARAMS(5, "Usage: RegisterSpeedrunDemo(<map>, <playerId>, <runId>, <mode>, <way>)");

		std::string map = Scr_GetString(0);
		std::string playerId = Scr_GetString(1);
		std::string runId = Scr_GetString(2);
		std::string mode = Scr_GetString(3);
		std::string way = Scr_GetString(4);

		Scr_AddBool(SR->DemoContainer->RegisterSpeedrunDemo(map, playerId, runId, mode, way));
	}

	void DemoCommands::PlayDemo(scr_entref_t num)
	{
		CHECK_PARAMS(1, "Usage: PlayDemo(<id>)");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		std::string id = Scr_GetString(0);

		auto player = SR->Players[num.entnum];
		auto demo = std::find_if(SR->DemoContainer->Demos.cbegin(), SR->DemoContainer->Demos.cend(),
			[&](const std::shared_ptr<Demo> &item) { return item->ID == id; });

		if (demo != std::end(SR->DemoContainer->Demos))
		{
			player->DemoPlayer->Play(*demo);
			Scr_AddEntity(player->DemoPlayer->Entity);
		}
	}

	void DemoCommands::IsDemoPlaying(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: IsDemoPlaying()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];
		Scr_AddBool(static_cast<qboolean>(!!player->DemoPlayer->Demo.get()));
	}

	void DemoCommands::GetSpeedrunVelocity(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: GetSpeedrunVelocity()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];

		Scr_AddInt(player->DemoPlayer->Velocity);
	}

	void DemoCommands::GetDemoWeapon(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: StopDemo()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];
		auto weapon = player->DemoPlayer->Weapon;

		if (!weapon.empty())
			Scr_AddString(weapon.c_str());
	}

	void DemoCommands::StopDemo(scr_entref_t num)
	{
		CHECK_PARAMS(0, "Usage: StopDemo()");

		gentity_t *ent = VM_GetGEntityForNum(num);

		if (!ent || !ent->client)
		{
			Scr_ObjectError("not a client\n");
			return;
		}
		auto player = SR->Players[num.entnum];

		player->DemoPlayer->Stop();
	}
}
