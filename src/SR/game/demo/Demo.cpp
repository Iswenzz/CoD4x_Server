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
		while (Reader->DemoFile->Next())
		{
			DemoFrame frame = { 0 };

			if (Reader->DemoFile->CurrentMessageType == Iswenzz::CoD4::DM1::MSGType::MSG_FRAME)
				continue;
			if (!Reader->GetCurrentSnapshot().valid)
				continue;

			auto ps = Reader->GetCurrentSnapshot().ps;
			auto archive = Reader->GetCurrentFrame();
			VectorCopy(archive.angles, ps.viewangles);

			frame.time = Reader->GetTimeMilliseconds();
			frame.fps = Reader->GetFPS();
			frame.ps = *reinterpret_cast<playerState_t *>(&ps);
			frame.playerName = Reader->GetPlayerName().netname;

			Frames.push_back(frame);
		}
		ConfigStrings = Reader->DemoFile->ConfigStrings;
		Weapons = Utils::SplitString(Reader->GetConfigString("defaultweapon_mp"), ' ');
		Reader->Close();
	}
}
