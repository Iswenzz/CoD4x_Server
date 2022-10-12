#include "Debug.hpp"
#include "utils/Log.hpp"

namespace Iswenzz::CoD4x
{
	void Debug::Initialize()
	{
		PacketSize = Cvar_RegisterBool("netchan_debug", qfalse, 0, "Debug the players packets.");
	}

	void Debug::NetchanPacketSize(int size)
	{
		if (!PacketSize->boolean)
			return;

		if (size >= 1050)
			Log::WriteLine("YELLOW: " + std::to_string(size));
		else if (size >= 200)
			Log::WriteLine("PACKET: " + std::to_string(size));
	}
}

using namespace Iswenzz::CoD4x;

C_EXTERN
{
	void NetchanDebugSize(int size)
	{
		Debug::NetchanPacketSize(size);
	}
}
