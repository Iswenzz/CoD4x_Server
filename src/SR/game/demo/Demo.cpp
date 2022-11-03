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
			while (Reader->Next())
			{
				DemoFrame frame = { 0 };

				if (Reader->DemoFile->CurrentMessageType == Iswenzz::CoD4::DM1::MSGType::MSG_FRAME)
					continue;
				if (!Reader->GetCurrentSnapshot().valid)
					continue;

				auto ps = Reader->GetCurrentSnapshot().ps;
				auto archive = Reader->GetCurrentFrame();
				auto entities = Reader->GetLastUpdatedEntities();

				frame.chat = ProcessChat();
				frame.time = Reader->GetTimeMilliseconds();
				frame.fps = Reader->GetFPS();
				frame.ps = *reinterpret_cast<playerState_t *>(&ps);
				frame.playerName = Reader->GetPlayerName().netname;
				frame.entities = *reinterpret_cast<std::vector<entityState_t>*>(&entities);

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
