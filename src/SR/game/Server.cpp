#include "Server.hpp"
#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Server::Server()
	{
		Vegas = std::make_unique<class Vegas>();
	}

	void Server::LoadMap()
	{

	}

	void Server::Frame()
	{
		for (const auto &player : SR->Players)
		{
			if (player)
				player->Frame();
		}
	}

	void Server::Sleep(int ms)
	{
		NET_Sleep(ms * 1000);
	}


	void Server::WaitFrame(int amount)
	{
		Sleep(50 * amount);
	}
}

C_EXTERN
{
	void SR_Frame()
	{
		SR->Server->Frame();
	}

	void SR_LoadMap()
	{
		SR->Server->LoadMap();
	}
}
