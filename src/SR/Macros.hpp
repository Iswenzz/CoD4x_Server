#pragma once

#define OPTIMIZE3 __optimize3
#define CDECL __cdecl
#define STDCALL __stdcall
#define C_EXTERN extern "C"

#define C_WRAPPER(reference, definition, args) \
C_EXTERN definition \
{ \
	return reference args; \
}

#define C_VARIABLE(definition) definition;

#define MAX_CLIENTS 64
