#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Server::Server()
	{
		Netchan = std::make_unique<class Netchan>();
		Render = std::make_unique<class Render>();
		Vegas = std::make_unique<class Vegas>();
		Speedrun = std::make_unique<class Demo>();

		CommandsContainer::Register();
		Debug::Initialize();
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
