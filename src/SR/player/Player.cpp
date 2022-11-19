#include "Player.hpp"
#include "SR.hpp"
#include "utils/Utils.hpp"
#include "utils/Log.hpp"

namespace Iswenzz::CoD4x
{
	Player::Player(client_t *cl)
	{
		this->cl = cl;
		this->ps = &cl->gentity->client->ps;

		this->DemoPlayer = std::make_unique<class DemoPlayer>(this);
		this->PMove = std::make_unique<class PMove>(this);

		this->SurfaceFlags = 0;
	}

	void Player::Spawn()
	{

	}

	void Player::CalculateFPS()
	{
		if (FrameTimes.empty())
			return;

		cl->clFPS = Utils::VectorAverageMode(FrameTimes);
		FrameTimes.clear();
	}

	void Player::Packet(msg_t *msg)
	{
		PreviousFrameTime = CurrentFrameTime;
		CurrentFrameTime = ps->commandTime;

		int frameDifference = (CurrentFrameTime - PreviousFrameTime);
		if (frameDifference > 0)
		{
			int fps = cl->clFrames * static_cast<double>(1000.0 / frameDifference);
			FrameTimes.push_back(fps);
			cl->clFrames = 0;
		}
		DemoPlayer->Packet();
	}

	void Player::Frame()
	{
		CalculateFPS();

		SR->Server->Vegas->Frame(this);
		DemoPlayer->Frame();
	}

	clientSnapshot_t *Player::GetFrame()
	{
		return &cl->frames[cl->netchan.outgoingSequence & PACKET_MASK];
	}
}

C_EXTERN
{
	void SR_InitializePlayer(client_t *cl)
	{
		if (!cl || !cl->gentity || !cl->gentity->client) return;

		Log::WriteLine("[Player] Connected %d", cl->gentity->client->ps.clientNum);

		SR->Players[cl->gentity->client->ps.clientNum] = std::make_shared<Player>(cl);
	}

	void SR_FreePlayer(client_t *cl)
	{
		if (!cl || !cl->gentity || !cl->gentity->client) return;

		Log::WriteLine("[Player] Disconnected %d", cl->gentity->client->ps.clientNum);
	}

	void SR_ClientSpawn(gclient_t *client)
	{
		if (!client) return;

		SR->Players[client->ps.clientNum]->Spawn();
	}
}
