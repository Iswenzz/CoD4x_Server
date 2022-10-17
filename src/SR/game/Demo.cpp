#include "Demo.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Demo::Demo(Player *player)
	{
		this->player = player;
	}

	Demo::~Demo()
	{
		Reader->Close();
	}

	void Demo::Open(std::string path)
	{
		Reader = std::make_unique<Iswenzz::CoD4::DM1::DemoReader>(path);
		StartTime = player->currentFrameTime;
	}

	void Demo::Frame()
	{
		if (!Reader || !Reader->IsOpen())
			return;

		if ((player->currentFrameTime - StartTime) > Reader->GetTimeMilliseconds())
			Reader->DemoFile->Next();
	}

	void Demo::PlayerFrame()
	{
		if (!Reader || !Reader->IsOpen())
			return;

		auto demoSnapshot = Reader->GetCurrentSnapshot();
		auto demoFrame = Reader->GetCurrentFrame();
		auto frame = player->GetFrame();
		auto originalFrame = *frame;

		// State
		memcpy(&frame->ps.sprintState, &demoSnapshot.ps.sprintState, sizeof(frame->ps.sprintState));
		memcpy(&frame->ps.mantleState, &demoSnapshot.ps.mantleState, sizeof(frame->ps.mantleState));
		memcpy(&frame->ps.actionSlotParam, &demoSnapshot.ps.actionSlotParam, sizeof(frame->ps.actionSlotParam));
		frame->ps.spreadOverrideState = demoSnapshot.ps.spreadOverrideState;
		frame->ps.pm_flags = demoSnapshot.ps.pm_flags;
		frame->ps.pm_time = demoSnapshot.ps.pm_time;
		frame->ps.pm_type = demoSnapshot.ps.pm_type;
		frame->ps.weapFlags = demoSnapshot.ps.weapFlags;
		frame->ps.weapAnim = demoSnapshot.ps.weapAnim;
		frame->ps.weaponTime = demoSnapshot.ps.weaponTime;
		frame->ps.aimSpreadScale = demoSnapshot.ps.aimSpreadScale;
		frame->ps.legsAnim = demoSnapshot.ps.legsAnim;
		frame->ps.eFlags = demoSnapshot.ps.eFlags;

		// Origin & Angles
		VectorCopy(demoFrame.origin, frame->ps.origin);
		SetClientViewAngle(player->cl->gentity, demoFrame.angles);
	}
}
