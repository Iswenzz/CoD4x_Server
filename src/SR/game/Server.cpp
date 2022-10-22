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
		SR->DemoContainer->Demos.clear();
	}

	void Server::Frame()
	{
		for (const auto &player : SR->Players)
		{
			if (player)
				player->Frame();
		}
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
