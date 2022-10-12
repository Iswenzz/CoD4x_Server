#include "Player.hpp"
#include "SR.hpp"

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

		this->fps = 0;
		this->frames = 0;
		this->speed = 0;
		this->surfaceFlags = 0;
	}
}

using namespace Iswenzz::CoD4x;

C_EXTERN void InitializePlayer(client_t *cl)
{
	auto player = std::make_shared<Player>(cl);
	player->Initialize();

	SR->Players[cl->gentity->client->ps.clientNum] = player;
}
