#include "DemoPlayer.hpp"
#include "player/Player.hpp"
#include "utils/Log.hpp"

namespace Iswenzz::CoD4x
{
	DemoPlayer::DemoPlayer(class Player *player)
	{
		this->Player = player;
	}

	void DemoPlayer::Play(const std::shared_ptr<class Demo>& demo)
	{
		Demo = demo;
		FrameIndex = 0;
		StartTime = Player->CurrentFrameTime;

		Entity = G_Spawn();
    	Scr_SetString(&Entity->classname, scr_const.script_origin);
		G_CallSpawnEntity(Entity);
	}

	void DemoPlayer::Stop()
	{
		Demo.reset();
	}

	DemoFrame DemoPlayer::GetFrame()
	{
		// Controls
		FrameIndex += Player->cl->lastUsercmd.forwardmove < 0 ? -1 : 1;

		if (FrameIndex >= Demo->Frames.size())
		{
			Demo.reset();
			return DemoFrame{ 0 };
		}
		return Demo->Frames.at(FrameIndex);
	}

	void DemoPlayer::RetrieveSpeedrunVelocity(const DemoFrame &frame)
	{
		if (frame.ps.velocity[0] == 0 || frame.ps.velocity[1] == 0 || frame.ps.velocity[2] == 0)
		{
			Velocity = sqrtl((frame.ps.velocity[0] * frame.ps.velocity[0]) + (frame.ps.velocity[1] * frame.ps.velocity[1]));
			return;
		}

		hudelem_t velocityHud;
		for (int i = 0; i < MAX_HUDELEMENTS; i++)
		{
			Log::WriteLine("scale: %f", frame.ps.hud.current[i].fontScale);

			if (frame.ps.hud.current[i].fontScale >= 1.55)
			{
				velocityHud = frame.ps.hud.current[i];
				break;
			}
		}
		Velocity = velocityHud.value;
	}

	void DemoPlayer::Frame()
	{
		if (!Demo)
			return;

		auto demoFrame = GetFrame();
		auto frame = Player->GetFrame();
		auto originalFrame = *frame;

		// Copy the demo frame to the player frame without huds.
		memcpy(&frame->ps, &demoFrame.ps, sizeof(playerState_t) - sizeof(frame->ps.hud));
		Player->cl->clFPS = demoFrame.fps;

		// State
		frame->ps.clientNum = originalFrame.ps.clientNum;
		frame->ps.commandTime = originalFrame.ps.commandTime;
		frame->ps.eFlags = originalFrame.ps.eFlags;
		frame->ps.pm_type = originalFrame.ps.pm_type;
		frame->ps.otherFlags = originalFrame.ps.otherFlags;
		frame->ps.viewlocked = originalFrame.ps.viewlocked;
		frame->ps.viewlocked_entNum = originalFrame.ps.viewlocked_entNum;
		frame->ps.viewHeightCurrent = originalFrame.ps.viewHeightCurrent;
		frame->ps.viewHeightLerpDown = originalFrame.ps.viewHeightLerpDown;
		frame->ps.viewHeightLerpTarget = originalFrame.ps.viewHeightLerpTarget;
		frame->ps.viewHeightLerpTime = originalFrame.ps.viewHeightLerpTime;
		frame->ps.viewHeightTarget = originalFrame.ps.viewHeightTarget;
		frame->ps.weaponstate = originalFrame.ps.weaponstate;
		frame->ps.groundEntityNum = originalFrame.ps.groundEntityNum;
		Vector2Copy(originalFrame.ps.viewAngleClampBase, frame->ps.viewAngleClampBase);
		Vector2Copy(originalFrame.ps.viewAngleClampRange, frame->ps.viewAngleClampRange);
		frame->ps.killCamEntity = originalFrame.ps.killCamEntity;
		memcpy(&frame->ps.stats, &originalFrame.ps.stats, sizeof(frame->ps.stats));

		// Weapon
		frame->ps.viewmodelIndex = originalFrame.ps.viewmodelIndex;
		frame->ps.weapon = originalFrame.ps.weapon;
		memcpy(&frame->ps.weapons, &originalFrame.ps.weapons, sizeof(frame->ps.weapons));
		memcpy(&frame->ps.weaponold, &originalFrame.ps.weaponold, sizeof(frame->ps.weaponold));
		memcpy(&frame->ps.weaponrechamber, &originalFrame.ps.weaponrechamber, sizeof(frame->ps.weaponrechamber));
		memcpy(&frame->ps.weaponmodels, &originalFrame.ps.weaponmodels, sizeof(frame->ps.weaponmodels));

		// Movement
		VectorCopy(originalFrame.ps.delta_angles, frame->ps.delta_angles);
		VectorCopy(demoFrame.ps.origin, frame->ps.origin);
		VectorCopy(demoFrame.ps.viewangles, Entity->r.currentAngles);
		RetrieveSpeedrunVelocity(demoFrame);
		SetClientViewAngle(Player->cl->gentity, demoFrame.ps.viewangles);
	}
}
