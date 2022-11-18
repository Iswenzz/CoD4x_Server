#include "Entity.hpp"
#include "SR.hpp"

C_EXTERN
{
	#include <scr_vm.h>
	#include <cscr_stringlist.h>
	#include <bg.h>
}

namespace Iswenzz::CoD4x
{
	void EntityCommands::Register()
	{
		Scr_AddFunction("playfxontag", PlayFXOnTag, qfalse);
	}

	void EntityCommands::PlayFXOnTag()
	{
		if (Scr_GetNumParam() != 3)
			Scr_Error("Incorrect number of parameters");

		int fxId = Scr_GetInt(0);
		if (fxId <= 0 || fxId >= 196)
			Scr_ParamError(0, fmt("effect id %i is invalid\n", fxId));

		gentity_t *ent = Scr_GetEntity(1);
		if (!ent->model)
			Scr_ParamError(1, "cannot play fx on entity with no model");

		int tagIndex = Scr_GetConstLowercaseString(2);
		const char *tagName = SL_ConvertToString(tagIndex);
		strchr(tagName, 34);

		if (SV_DObjGetBoneIndex(ent, tagIndex) < 0)
		{
			SV_DObjDumpInfo(ent);
			const char *modelName = SL_ConvertToString(G_ModelName(ent->model));
			Scr_ParamError(2, fmt("tag '%s' does not exist on entity with model '%s'", tagName, modelName));
		}
		int csIndex = G_FindConfigstringIndex(fmt("%02d%s", fxId, tagName), 1698, 256, 1, 0);
		const char *csName = SL_ConvertToString(csIndex);

		G_AddEvent(ent, EV_PLAY_FX_ON_TAG, csIndex);
		if (SR->Entities[ent->s.number])
			SR->Entities[ent->s.number]->HasFxOnTag = true;
	}
}
