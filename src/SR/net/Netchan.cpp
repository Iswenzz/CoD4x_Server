#include "Netchan.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	void Netchan::Packet(netadr_t *from, client_t* cl, msg_t *msg)
	{
		if (!cl || !cl->gentity)
			return;

		auto player = SR->Players[cl->gentity->client->ps.clientNum];
		if (player)
			player->Packet(msg);
	}
}

C_EXTERN
{
	void SR_Packet(netadr_t *from, client_t* cl, msg_t *msg)
	{
		SR->Netchan->Packet(from, cl, msg);
	}
}
