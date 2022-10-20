#include "DemoPlayer.hpp"
#include "player/Player.hpp"

namespace Iswenzz::CoD4x
{
	DemoPlayer::DemoPlayer(class Player *player)
	{
		this->Player = player;
	}

	void DemoPlayer::Play(const std::shared_ptr<class Demo>& demo)
	{
		FrameIndex = 0;
		StartTime = Player->CurrentFrameTime;

		Entity = G_Spawn();
    	Scr_SetString(&Entity->classname, scr_const.script_origin);
		G_CallSpawnEntity(Entity);
	}

	DemoFrame DemoPlayer::GetFrame()
	{
		// Controls
		FrameIndex += Player->cl->lastUsercmd.forwardmove < 0 ? -1 : 1;

		return FrameIndex < Demo->Frames.size() ? Demo->Frames.at(FrameIndex) : DemoFrame{ 0 };
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
		Vector2Copy(demoFrame.ps.oldVelocity, frame->ps.oldVelocity);
		VectorCopy(demoFrame.ps.velocity, frame->ps.velocity);
		VectorCopy(demoFrame.ps.viewangles, Entity->r.currentAngles);
		SetClientViewAngle(Player->cl->gentity, demoFrame.ps.viewangles);
	}
}
