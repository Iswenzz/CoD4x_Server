#include "Log.hpp"
#include <stdarg.h>

namespace Iswenzz::CoD4x
{
	void Log::WriteLine(const char *fmt, ...)
	{
		va_list	argptr;
		char msg[4096];

		va_start(argptr, fmt);
		Q_vsnprintf(msg, sizeof(msg), fmt, argptr);
		va_end(argptr);

		fprintf(stderr, "%s\n", msg);
	}

	void Log::Write(const char *fmt, ...)
	{
		va_list	argptr;
		char msg[4096];

		va_start(argptr, fmt);
		Q_vsnprintf(msg, sizeof(msg), fmt, argptr);
		va_end(argptr);

		fprintf(stderr, "%s", msg);
	}
}
