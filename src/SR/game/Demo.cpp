#include "Demo.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Demo::~Demo()
	{
		Reader->Close();
	}

	void Demo::Frame(Player *player)
	{
		if (!Reader || !Reader->IsOpen())
			return;

		if ((player->currentFrameTime - StartTime) > Reader->GetTimeMilliseconds())
			Reader->DemoFile->Next();
	}

	void Demo::PlayerFrame(Player *player)
	{
		if (!Reader || !Reader->IsOpen())
			return;

		auto demoSnapshot = Reader->GetCurrentSnapshot();
		auto demoFrame = Reader->GetCurrentFrame();
		auto frame = player->GetFrame();

		VectorCopy(demoFrame.origin, frame->ps.origin);
		VectorCopy(demoFrame.angles, frame->ps.viewangles);
	}
}
