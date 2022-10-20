#include "SR.hpp"

namespace Iswenzz::CoD4x
{
	Game::Game()
	{
		Iswenzz::CoD4::DM1::Huffman::InitMain();

		Server = std::make_unique<class Server>();
		Netchan = std::make_unique<class Netchan>();
		DemoContainer = std::make_unique<class DemoContainer>();

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
