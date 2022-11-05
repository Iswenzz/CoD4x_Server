#include "Demo.hpp"
#include "Utils/Utils.hpp"

namespace Iswenzz::CoD4x
{
	Demo::Demo(std::string id, std::string path)
	{
		ID = id;
		Reader = std::make_unique<Iswenzz::CoD4::DM1::DemoReader>(path);

		Open();
	}

	Demo::~Demo()
	{
		Reader->Close();
	}

	void Demo::Open()
	{
		try
		{
			DemoFrame previousFrame = { 0 };

			while (Reader->Next())
			{
				DemoFrame frame = { 0 };

				if (Reader->DemoFile->CurrentMessageType == Iswenzz::CoD4::DM1::MSGType::MSG_FRAME)
					continue;
				if (!Reader->GetCurrentSnapshot().valid)
					continue;

				auto ps = Reader->GetCurrentSnapshot().ps;
				auto archive = Reader->GetCurrentFrame();

				frame.chat = ProcessChat();
				frame.time = Reader->GetTimeMilliseconds();
				frame.fps = Reader->GetFPS();
				frame.ps = *reinterpret_cast<playerState_t *>(&ps);
				frame.playerName = Reader->GetPlayerName().netname;
				frame.entities = previousFrame.entities;
				frame.forwardmove = *(char *)&ps.dofNearStart;
				frame.rightmove = *(char *)&ps.dofNearEnd;
				frame.buttons = *(int *)&ps.dofFarStart;

				for (auto &ent : Reader->GetLastUpdatedEntities())
				{
					if (ent.eType == ET_SCRIPTMOVER)
						frame.entities[ent.number] = *reinterpret_cast<entityState_t*>(&ent);
				}

				previousFrame = frame;
				Frames.push_back(frame);
			}

			ConfigStrings = Reader->DemoFile->ConfigStrings;
			Weapons = Utils::SplitString(Reader->GetConfigString("defaultweapon_mp"), ' ');
			Reader->Close();
		}
		catch (...) { }
	}

	std::vector<std::string> Demo::ProcessChat()
	{
		std::vector<std::string> chat;
		std::vector<std::string> commands = Reader->GetLastCommandStrings();

		for (const std::string& command : commands)
		{
			if (command[0] == 'h')
				chat.push_back(command.substr(3, command.size() - 4));
		}
		return chat;
	}
}
