#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Server::Server()
	{
		Render = std::make_unique<class Render>();
		CommandsContainer::Register();
	}

	Server::~Server()
	{

	}
}

Server *SR;

C_EXTERN void SR_Initialize()
{
	SR = new Server();
}

C_EXTERN void SR_Shutdown()
{
	SR->~Server();
}
