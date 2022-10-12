#include "Log.hpp"

namespace Iswenzz::CoD4x
{
	void Log::WriteLine(std::string message)
	{
		fprintf(stderr, "%s\n", message.c_str());
	}

	void Log::Write(std::string message)
	{
		fprintf(stderr, "%s", message.c_str());
	}
}
