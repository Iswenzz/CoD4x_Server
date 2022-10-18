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

		// Copy the demo frame to the player frame without huds.
		memcpy(&frame->ps, &demoSnapshot.ps, sizeof(playerState_t) - sizeof(frame->ps.hud));

		// State
		frame->ps.clientNum = originalFrame.ps.clientNum;
		frame->ps.commandTime = originalFrame.ps.commandTime;
		frame->ps.eFlags = originalFrame.ps.eFlags;
		frame->ps.pm_type = originalFrame.ps.pm_type;
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
		VectorCopy(demoFrame.origin, frame->ps.origin);
		Vector2Copy(demoSnapshot.ps.oldVelocity, frame->ps.oldVelocity);
		VectorCopy(demoSnapshot.ps.velocity, frame->ps.velocity);
		VectorCopy(demoFrame.angles, Entity->r.currentAngles);
		SetClientViewAngle(Player->cl->gentity, demoFrame.angles);
	}
}
