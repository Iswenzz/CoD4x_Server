#include "Command.hpp"

C_EXTERN
{
	#include <q_shared.h>
	#include <qcommon_io.h>
	#include <qcommon_mem.h>
	#include <scr_vm.h>

	scr_method_t *scr_methods;
}

namespace Iswenzz::SR::CoD4x
{
	bool Command::Method(std::string name, std::function<void(const Command&, scr_entref_t)> method, bool developer)
	{
		scr_method_t *cmd;

		for (cmd = scr_methods; cmd; cmd = cmd->next)
		{
			if (name == cmd->name)
			{
				Com_PrintWarning(CON_CHANNEL_SCRIPT, "Scr_AddMethod: %s already defined\n", name);
				return false;
			}
		}

		// Small malloc to avoid zone fragmentation
		cmd = (scr_method_t*)S_Malloc( sizeof( scr_function_t ) + name.size() + 1);
		strcpy((char*)(cmd + 1), name.c_str());
		cmd->name = (char*)(cmd + 1);
		cmd->function = [](scr_entref_t ref) {  };
		cmd->developer = (qboolean)developer;
		cmd->next = scr_methods;
		scr_methods = cmd;
		return true;
	}
}
