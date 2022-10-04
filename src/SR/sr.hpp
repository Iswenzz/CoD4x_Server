#pragma once

#define OPTIMIZE3 __optimize3
#define CDECL __cdecl
#define STDCALL __stdcall

#define C_WRAPPER(reference, definition, args) \
extern "C" definition \
{ \
	return reference args; \
}

#define C_VARIABLE(definition) definition;
