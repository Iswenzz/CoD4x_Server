#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Server::Server()
	{
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
