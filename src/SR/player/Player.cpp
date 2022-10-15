#include "Player.hpp"
#include "SR.hpp"
#include "utils/Utils.hpp"

namespace Iswenzz::CoD4x
{
	Player::Player(client_t *cl)
	{
		this->cl = std::unique_ptr<client_t>(cl);
		this->ps = std::unique_ptr<playerState_t>(&cl->gentity->client->ps);
	}

	void Player::Initialize()
	{
		this->pmove = std::make_unique<PMove>(this);

		this->speed = 0;
		this->surfaceFlags = 0;
	}

	void Player::CalculateFPS()
	{
		if (frameTimes.empty())
			return;

		cl->clFPS = Utils::VectorAverageMode(frameTimes);
		frameTimes.clear();
	}

	void Player::Packet(msg_t *msg)
	{
		if (ps->commandTime > currentFrameTime)
		{
			previousFrameTime = currentFrameTime;
			currentFrameTime = ps->commandTime;
			frameTimes.push_back(1000 / (currentFrameTime - previousFrameTime));
		}
	}

	void Player::Frame()
	{
		CalculateFPS();
		SR->Vegas->Frame(this);
	}

	clientSnapshot_t *Player::GetFrame()
	{
		return &cl->frames[cl->netchan.outgoingSequence & PACKET_MASK];
	}
}

C_EXTERN
{
	void InitializePlayer(client_t *cl)
	{
		auto player = std::make_shared<Player>(cl);
		player->Initialize();

		SR->Players[cl->gentity->client->ps.clientNum] = player;
	}
}
