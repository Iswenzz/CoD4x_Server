#include "Demo.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Demo::Demo(class Player *player)
	{
		this->Player = player;
	}

	Demo::~Demo()
	{
		Reader->Close();
	}

	void Demo::Open(std::string path)
	{
		Reader = std::make_unique<Iswenzz::CoD4::DM1::DemoReader>(path);
		StartTime = Player->CurrentFrameTime;

		Entity = G_Spawn();
    	Scr_SetString(&Entity->classname, scr_const.script_origin);
		G_CallSpawnEntity(Entity);
	}

	void Demo::Frame()
	{
		if (!Reader || !Reader->IsOpen())
			return;

		if ((Player->CurrentFrameTime - StartTime) > Reader->GetTimeMilliseconds())
			Reader->DemoFile->Next();
	}

	void Demo::PlayerFrame()
	{
		if (!Reader || !Reader->IsOpen())
			return;

		auto demoSnapshot = Reader->GetCurrentSnapshot();
		auto demoFrame = Reader->GetCurrentFrame();
		auto frame = Player->GetFrame();
		auto originalFrame = *frame;

		// State
		memcpy(&frame->ps.sprintState, &demoSnapshot.ps.sprintState, sizeof(frame->ps.sprintState));
		memcpy(&frame->ps.mantleState, &demoSnapshot.ps.mantleState, sizeof(frame->ps.mantleState));
		memcpy(&frame->ps.actionSlotParam, &demoSnapshot.ps.actionSlotParam, sizeof(frame->ps.actionSlotParam));
		// frame->ps.eFlags = demoSnapshot.ps.eFlags;
		// frame->ps.viewmodelIndex = demoSnapshot.ps.viewmodelIndex;
		// frame->ps.clientNum = demoSnapshot.ps.clientNum;
		// frame->ps.commandTime = demoSnapshot.ps.commandTime;
		// frame->ps.pm_type = demoSnapshot.ps.pm_type;
		frame->ps.spreadOverride = demoSnapshot.ps.spreadOverride;
		frame->ps.spreadOverrideState = demoSnapshot.ps.spreadOverrideState;
		frame->ps.bobCycle = demoSnapshot.ps.bobCycle;
		frame->ps.otherFlags = demoSnapshot.ps.otherFlags;
		frame->ps.foliageSoundTime = demoSnapshot.ps.foliageSoundTime;
		frame->ps.pm_flags = demoSnapshot.ps.pm_flags;
		frame->ps.pm_time = demoSnapshot.ps.pm_time;
		frame->ps.aimSpreadScale = demoSnapshot.ps.aimSpreadScale;
		frame->ps.adsDelayTime = demoSnapshot.ps.adsDelayTime;
		frame->ps.legsAnim = demoSnapshot.ps.legsAnim;
		frame->ps.legsAnimDuration = demoSnapshot.ps.legsAnimDuration;
		frame->ps.torsoAnim = demoSnapshot.ps.torsoAnim;
		frame->ps.torsoAnimDuration = demoSnapshot.ps.torsoAnimDuration;
		frame->ps.flinchYawAnim = demoSnapshot.ps.flinchYawAnim;
		frame->ps.groundEntityNum = demoSnapshot.ps.groundEntityNum;
		VectorCopy(demoSnapshot.ps.vLadderVec, frame->ps.vLadderVec);
		frame->ps.damageYaw = demoSnapshot.ps.damageYaw;
		frame->ps.damagePitch = demoSnapshot.ps.damagePitch;
		frame->ps.damageEvent = demoSnapshot.ps.damageEvent;
		frame->ps.damageCount = demoSnapshot.ps.damageCount;
		frame->ps.damageTimer = demoSnapshot.ps.damageTimer;
		frame->ps.damageDuration = demoSnapshot.ps.damageDuration;
		frame->ps.movementDir = demoSnapshot.ps.movementDir;
		frame->ps.eventSequence = demoSnapshot.ps.eventSequence;
		frame->ps.oldEventSequence = demoSnapshot.ps.oldEventSequence;
		memcpy(&frame->ps.events, &demoSnapshot.ps.events, sizeof(frame->ps.events));
		memcpy(&frame->ps.eventParms, &demoSnapshot.ps.eventParms, sizeof(frame->ps.eventParms));
		frame->ps.proneDirection = demoSnapshot.ps.proneDirection;
		frame->ps.proneDirectionPitch = demoSnapshot.ps.proneDirectionPitch;
		frame->ps.proneTorsoPitch = demoSnapshot.ps.proneTorsoPitch;
		// frame->ps.viewlocked = demoSnapshot.ps.viewlocked;
		// frame->ps.viewlocked_entNum = demoSnapshot.ps.viewlocked_entNum;
		frame->ps.cursorHint = demoSnapshot.ps.cursorHint;
		frame->ps.cursorHintEntIndex = demoSnapshot.ps.cursorHintEntIndex;
		frame->ps.cursorHintString = demoSnapshot.ps.cursorHintString;
		frame->ps.locationSelectionInfo = demoSnapshot.ps.locationSelectionInfo;
		frame->ps.fTorsoPitch = demoSnapshot.ps.fTorsoPitch;
		frame->ps.fWaistPitch = demoSnapshot.ps.fWaistPitch;
		frame->ps.holdBreathScale = demoSnapshot.ps.holdBreathScale;
		frame->ps.holdBreathTimer = demoSnapshot.ps.holdBreathTimer;
		frame->ps.meleeChargeYaw = demoSnapshot.ps.meleeChargeYaw;
		frame->ps.meleeChargeTime = demoSnapshot.ps.meleeChargeTime;
		frame->ps.meleeChargeDist = demoSnapshot.ps.meleeChargeDist;
		memcpy(&frame->ps.actionSlotType, &demoSnapshot.ps.actionSlotType, sizeof(frame->ps.actionSlotType));
		memcpy(&frame->ps.actionSlotParam, &demoSnapshot.ps.actionSlotParam, sizeof(frame->ps.actionSlotParam));
		frame->ps.entityEventSequence = demoSnapshot.ps.entityEventSequence;
		frame->ps.shellshockIndex = demoSnapshot.ps.shellshockIndex;
		frame->ps.shellshockDuration = demoSnapshot.ps.shellshockDuration;
		frame->ps.shellshockTime = demoSnapshot.ps.shellshockTime;
		frame->ps.dofNearStart = demoSnapshot.ps.dofNearStart;
		frame->ps.dofNearEnd = demoSnapshot.ps.dofNearEnd;
		frame->ps.dofFarStart = demoSnapshot.ps.dofFarStart;
		frame->ps.dofFarEnd = demoSnapshot.ps.dofFarEnd;
		frame->ps.dofNearBlur = demoSnapshot.ps.dofNearBlur;
		frame->ps.dofViewmodelStart = demoSnapshot.ps.dofViewmodelStart;
		frame->ps.dofViewmodelEnd = demoSnapshot.ps.dofViewmodelEnd;
		frame->ps.hudElemLastAssignedSoundID = demoSnapshot.ps.hudElemLastAssignedSoundID;
		frame->ps.deltaTime = demoSnapshot.ps.deltaTime;

		// Weapon
		frame->ps.weapFlags = demoSnapshot.ps.weapFlags;
		frame->ps.weapAnim = demoSnapshot.ps.weapAnim;
		frame->ps.weaponTime = demoSnapshot.ps.weaponTime;
		frame->ps.weaponDelay = demoSnapshot.ps.weaponDelay;
		frame->ps.grenadeTimeLeft = demoSnapshot.ps.grenadeTimeLeft;
		frame->ps.weaponRestrictKickTime = demoSnapshot.ps.weaponRestrictKickTime;
		frame->ps.offHandIndex = demoSnapshot.ps.offHandIndex;
		memcpy(&frame->ps.offhandSecondary, &demoSnapshot.ps.offhandSecondary, sizeof(frame->ps.offhandSecondary));
		frame->ps.fWeaponPosFrac = demoSnapshot.ps.fWeaponPosFrac;

		// Movement
		frame->ps.leanf = demoSnapshot.ps.leanf;
		frame->ps.gravity = demoSnapshot.ps.gravity;
		frame->ps.speed = demoSnapshot.ps.speed;
		frame->ps.moveSpeedScaleMultiplier = demoSnapshot.ps.moveSpeedScaleMultiplier;
		frame->ps.jumpOriginZ = demoSnapshot.ps.jumpOriginZ;
		frame->ps.jumpTime = demoSnapshot.ps.jumpTime;
		VectorCopy(demoFrame.origin, frame->ps.origin);
		Vector2Copy(demoSnapshot.ps.oldVelocity, frame->ps.oldVelocity);
		VectorCopy(demoSnapshot.ps.velocity, frame->ps.velocity);
		VectorCopy(demoFrame.angles, Entity->r.currentAngles);
		SetClientViewAngle(Player->cl->gentity, demoFrame.angles);
	}
}
