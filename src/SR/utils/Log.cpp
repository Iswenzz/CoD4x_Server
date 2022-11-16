#include "Log.hpp"
#include <stdarg.h>

namespace Iswenzz::CoD4x
{
	void Log::Print(conChannel_t channel, std::string msg)
	{
		if (channel == CON_CHANNEL_SR_DEBUG)
			Log::Write(msg);
	}

	void Log::WriteLine(std::string fmt, ...)
	{
		va_list	argptr;
		char msg[4096];

		const char *cfmt = fmt.c_str();

		va_start(argptr, cfmt);
		Q_vsnprintf(msg, sizeof(msg), cfmt, argptr);
		va_end(argptr);

		fprintf(stderr, "%s\n", msg);
	}

	void Log::Write(std::string fmt, ...)
	{
		va_list	argptr;
		char msg[4096];

		const char *cfmt = fmt.c_str();

		va_start(argptr, cfmt);
		Q_vsnprintf(msg, sizeof(msg), cfmt, argptr);
		va_end(argptr);

		fprintf(stderr, "%s", msg);
	}
}

C_EXTERN
{
	void SR_Print(conChannel_t channel, char *msg)
	{
		Log::Print(channel, msg);
	}
}
