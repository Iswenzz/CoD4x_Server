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

	void DemoPlayer::RetrieveSpeedrunVelocity()
	{
		int frameVelocity = 0;
		if (CurrentFrame.ps.velocity[0] != 0 || CurrentFrame.ps.velocity[1] != 0 || CurrentFrame.ps.velocity[2] != 0)
			frameVelocity = sqrtl((CurrentFrame.ps.velocity[0] * CurrentFrame.ps.velocity[0]) + (CurrentFrame.ps.velocity[1] * CurrentFrame.ps.velocity[1]));

		hudelem_t velocityHud;
		for (int i = 0; i < MAX_HUDELEMENTS; i++)
		{
			if ((std::abs(CurrentFrame.ps.hud.current[i].fontScale - 1.6) <= 0.05 ||
				std::abs(CurrentFrame.ps.hud.current[i].fontScale - 1.8) <= 0.05) &&
				CurrentFrame.ps.hud.current[i].value > 0)
			{
				velocityHud = CurrentFrame.ps.hud.current[i];
				break;
			}
		}
		Velocity = frameVelocity >= velocityHud.value ? frameVelocity : velocityHud.value;
	}

	void DemoPlayer::UpdateEntity(snapshotInfo_t *snapInfo, msg_t* msg, const int time, entityState_t* from, entityState_t* to, qboolean force)
	{
		if (!to)
		{
			MSG_WriteDeltaEntity(snapInfo, msg, time, from, to, force);
			return;
		}
		entityState_t entity = *to;

		auto it = CurrentFrame.entities.find(to->number);
		if (it != CurrentFrame.entities.end())
		{
			entityState_t demoEntity = it->second;
			vec3_t pos;

			entity.lerp.pos.trType = TR_STATIONARY;
			entity.lerp.pos.trTime = 0;
			entity.lerp.pos.trDuration = 0;
			BG_EvaluateTrajectory(&demoEntity.lerp.pos, CurrentFrame.ps.commandTime, pos);
			VectorCopy(demoEntity.lerp.pos.trDelta, entity.lerp.pos.trDelta);
			VectorCopy(pos, entity.lerp.pos.trBase);

			entity.lerp.apos.trType = TR_STATIONARY;
			entity.lerp.apos.trTime = 0;
			entity.lerp.apos.trDuration = 0;
			BG_EvaluateTrajectory(&demoEntity.lerp.apos, CurrentFrame.ps.commandTime, pos);
			VectorCopy(demoEntity.lerp.apos.trDelta, entity.lerp.apos.trDelta);
			VectorCopy(pos, entity.lerp.apos.trBase);
		}
		MSG_WriteDeltaEntity(snapInfo, msg, time, from, &entity, force);
	}

	bool DemoPlayer::ComputeFrame()
	{
		// Controls
		int direction = Player->cl->lastUsercmd.forwardmove < 0 ? -1 : 1;
		PreviousFrameIndex = FrameIndex;
		Slowmo = Player->cl->lastUsercmd.buttons & KEY_MASK_JUMP;
		FrameIndex += !Slowmo ? direction : 0;

		// Slowmo
		if (SlowmoIndex > 10 || SlowmoIndex < 0)
		{
			SlowmoIndex = 0;
			FrameIndex += direction;
		}
		// EOF
		if (FrameIndex >= Demo->Frames.size())
		{
			Demo.reset();
			return false;
		}
		DemoFrame frame = Demo->Frames.at(FrameIndex);

		if (Slowmo)
		{
			int interpolateIndex = FrameIndex + direction;
			if (interpolateIndex < 0 || interpolateIndex >= Demo->Frames.size())
				return false;

			DemoFrame interpolateFrame = Demo->Frames.at(interpolateIndex);
			float interpolate = static_cast<float>(SlowmoIndex) / 10;

			frame.ps.origin[0] = std::lerp(frame.ps.origin[0], interpolateFrame.ps.origin[0], interpolate);
			frame.ps.origin[1] = std::lerp(frame.ps.origin[1], interpolateFrame.ps.origin[1], interpolate);
			frame.ps.origin[2] = std::lerp(frame.ps.origin[2], interpolateFrame.ps.origin[2], interpolate);

			frame.ps.viewangles[0] = std::lerp(frame.ps.viewangles[0], interpolateFrame.ps.viewangles[0], interpolate);
			frame.ps.viewangles[1] = std::lerp(frame.ps.viewangles[1], interpolateFrame.ps.viewangles[1], interpolate);
			frame.ps.viewangles[2] = std::lerp(frame.ps.viewangles[2], interpolateFrame.ps.viewangles[2], interpolate);

			SlowmoIndex++;
		}
		CurrentFrame = frame;
		return true;
	}

	void DemoPlayer::Packet()
	{
		if (!Demo || FrameIndex == PreviousFrameIndex) return;

		playerState_t originalPS = *Player->ps;

		// Copy the demo frame to the player without huds.
		memcpy(Player->ps, &CurrentFrame.ps, sizeof(playerState_t) - sizeof(CurrentFrame.ps.hud));
		Player->cl->clFPS = CurrentFrame.fps;

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
		int weaponId = CurrentFrame.ps.weapon - 1;
		Weapon = weaponId < Demo->Weapons.size() && weaponId >= 0 ? Demo->Weapons[weaponId] : "";

		// Movement
		VectorCopy(originalPS.delta_angles, Player->ps->delta_angles);
		VectorCopy(CurrentFrame.ps.viewangles, Entity->r.currentAngles);
		VectorCopy(CurrentFrame.ps.origin, Player->ps->origin);
	}

	void DemoPlayer::Frame()
	{
		if (!Demo || !ComputeFrame()) return;

		clientSnapshot_t *frame = Player->GetFrame();

		// Movement
		VectorCopy(CurrentFrame.ps.origin, frame->ps.origin);
		SetClientViewAngle(Player->cl->gentity, CurrentFrame.ps.viewangles);
		RetrieveSpeedrunVelocity();

		// Commands
		for (const std::string &message : CurrentFrame.chat)
			SV_SendServerCommand(Player->cl, "h \"^5[Demo] ^7%s\"", message.c_str());
	}
}

C_EXTERN
{
	qboolean SR_DemoIsPlaying(client_t *cl)
	{
		return static_cast<qboolean>(!!(cl && SR->Players[cl->gentity->client->ps.clientNum]->DemoPlayer->Demo));
	}

	void SR_DemoUpdateEntity(client_t *cl, snapshotInfo_t *snapInfo, msg_t* msg, const int time, entityState_t* from, entityState_t* to, qboolean force)
	{
		if (!cl) return;

		auto player = SR->Players[cl->gentity->client->ps.clientNum];
		player->DemoPlayer->UpdateEntity(snapInfo, msg, time, from, to, force);
	}
}
