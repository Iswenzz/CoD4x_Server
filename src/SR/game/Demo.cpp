#include "Demo.hpp"

namespace Iswenzz::CoD4x
{
	Demo::Demo()
	{
		std::string path = R"(D:\Vids\CoD4\izengine\mp_dr_darmuhv2.dm_1)";
		Reader = std::make_unique<Iswenzz::CoD4::DM1::DemoReader>();
		auto a = Reader->IsOpen();
	}

	Demo::~Demo()
	{

	}

	void Demo::PlayDemo()
	{

	}
}
