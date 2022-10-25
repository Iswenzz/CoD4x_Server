#include "DemoPlayer.hpp"
#include "player/Player.hpp"
#include "utils/Log.hpp"
#include "utils/Utils.hpp"

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

	void DemoPlayer::RetrieveSpeedrunVelocity(const DemoFrame &frame)
	{
		int frameVelocity = 0;
		if (frame.ps.velocity[0] != 0 || frame.ps.velocity[1] != 0 || frame.ps.velocity[2] != 0)
			frameVelocity = sqrtl((frame.ps.velocity[0] * frame.ps.velocity[0]) + (frame.ps.velocity[1] * frame.ps.velocity[1]));

		hudelem_t velocityHud;
		for (int i = 0; i < MAX_HUDELEMENTS; i++)
		{
			if ((std::abs(frame.ps.hud.current[i].fontScale - 1.6) <= 0.05 ||
				std::abs(frame.ps.hud.current[i].fontScale - 1.8) <= 0.05) &&
				frame.ps.hud.current[i].value > 0)
			{
				velocityHud = frame.ps.hud.current[i];
				break;
			}
		}
		Velocity = frameVelocity >= velocityHud.value ? frameVelocity : velocityHud.value;
	}

	DemoFrame DemoPlayer::GetFrame()
	{
		if (FrameIndex >= Demo->Frames.size())
		{
			Demo.reset();
			return DemoFrame{ 0 };
		}
		return Demo->Frames.at(FrameIndex);
	}

	void DemoPlayer::Packet()
	{
		if (!Demo || FrameIndex == PreviousFrameIndex) return;

		DemoFrame demoFrame = GetFrame();
		playerState_t originalPS = *Player->ps;

		// Copy the demo frame to the player without huds.
		memcpy(Player->ps, &demoFrame.ps, sizeof(playerState_t) - sizeof(demoFrame.ps.hud));
		Player->cl->clFPS = demoFrame.fps;

		// State
		Player->ps->clientNum = originalPS.clientNum;
		Player->ps->commandTime = originalPS.commandTime;
		Player->ps->viewlocked = originalPS.viewlocked;
		Player->ps->viewlocked_entNum = originalPS.viewlocked_entNum;
		Player->ps->viewHeightCurrent = originalPS.viewHeightCurrent;
		Player->ps->viewHeightLerpDown = originalPS.viewHeightLerpDown;
		Player->ps->viewHeightLerpTarget = originalPS.viewHeightLerpTarget;
		Player->ps->viewHeightLerpTime = originalPS.viewHeightLerpTime;
		Player->ps->viewHeightTarget = originalPS.viewHeightTarget;
		Player->ps->pm_type = originalPS.pm_type;
		Player->ps->eFlags = originalPS.eFlags;
		Player->ps->otherFlags = originalPS.otherFlags;
		Player->ps->pm_flags &= ~PMF_PRONING;
		Player->ps->pm_flags &= ~PMF_CROUCHING;
		Vector2Copy(originalPS.viewAngleClampBase, Player->ps->viewAngleClampBase);
		Vector2Copy(originalPS.viewAngleClampRange, Player->ps->viewAngleClampRange);
		Player->ps->killCamEntity = originalPS.killCamEntity;
		memcpy(&Player->ps->stats, &originalPS.stats, sizeof(Player->ps->stats));

		// Weapon
		Player->ps->viewmodelIndex = originalPS.viewmodelIndex;
		Player->ps->weapon = originalPS.weapon;
		Player->ps->weaponstate = originalPS.weaponstate;
		memcpy(&Player->ps->ammo, &originalPS.ammo, sizeof(Player->ps->ammo));
		memcpy(&Player->ps->ammoclip, &originalPS.ammoclip, sizeof(Player->ps->ammoclip));
		memcpy(&Player->ps->weapons, &originalPS.weapons, sizeof(Player->ps->weapons));
		memcpy(&Player->ps->weaponold, &originalPS.weaponold, sizeof(Player->ps->weaponold));
		memcpy(&Player->ps->weaponrechamber, &originalPS.weaponrechamber, sizeof(Player->ps->weaponrechamber));
		memcpy(&Player->ps->weaponmodels, &originalPS.weaponmodels, sizeof(Player->ps->weaponmodels));
		int weaponId = demoFrame.ps.weapon - 1;
		Weapon = weaponId < Demo->Weapons.size() && weaponId >= 0 ? Demo->Weapons[weaponId] : "";

		// Movement
		VectorCopy(originalPS.delta_angles, Player->ps->delta_angles);
		VectorCopy(demoFrame.ps.viewangles, Entity->r.currentAngles);
		VectorCopy(demoFrame.ps.origin, Player->ps->origin);
		SetClientViewAngle(Player->cl->gentity, demoFrame.ps.viewangles);
	}

	void DemoPlayer::Frame()
	{
		if (!Demo) return;

		// Controls
		PreviousFrameIndex = FrameIndex;
		FrameIndex += Player->cl->lastUsercmd.forwardmove < 0 ? -1 : 1;

		// EOF
		if (FrameIndex >= Demo->Frames.size())
		{
			Demo.reset();
			return;
		}

		DemoFrame demoFrame = GetFrame();
		clientSnapshot_t *frame = Player->GetFrame();

		// Movement
		VectorCopy(demoFrame.ps.origin, frame->ps.origin);
		RetrieveSpeedrunVelocity(demoFrame);
	}
}
