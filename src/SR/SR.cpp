#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Game::Game()
	{
		Server = std::make_unique<class Server>();
		Netchan = std::make_unique<class Netchan>();

		CommandsContainer::Register();
		Debug::Initialize();
	}

	Game::~Game()
	{

	}
}

Game *SR;

C_EXTERN void SR_Initialize()
{
	SR = new Game();
}

C_EXTERN void SR_Shutdown()
{
	SR->~Game();
}
