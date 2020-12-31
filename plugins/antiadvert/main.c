#include "regex.h"

#ifndef PLUGIN_INCLUDES
#include "../pinc.h"
#endif

#define RE_COUNT 3

typedef struct
{
	struct dre2 *re[RE_COUNT];
} scan_t;

static scan_t scan;

PCL void OnMessageSent(char *message, int slot, qboolean *show, int type)
{
	for (int i = 0; i < RE_COUNT; i++)
	{
		regex_items *matches = NULL;
		if (scan.re[i])
		{
			matches = dre2_get_matches(scan.re[i], (unsigned char *)message);
			if (matches)
			{
				qboolean triggered = matches->count > 0;
				cleanup_dre2_matches(matches);
				
				if (triggered) // if anti advert pattern trigger
				{
					strcpy(message, "^1[Message removed for advertisement]");
					return;
				}
			}
		}
	}
}

PCL int OnInit()
{
	scan.re[0] = dre2_parse((unsigned char*)".*\\d.*\\..*\\d.*\\..*\\d.*\\..*\\d", DRE2_GREEDY);
	scan.re[1] = dre2_parse((unsigned char*)".*\\d.*_.*\\d.*_.*\\d.*_.*\\d", DRE2_GREEDY);
	scan.re[2] = dre2_parse((unsigned char*)".*\\d.*-.*\\d.*-.*\\d.*-.*\\d", DRE2_GREEDY);

	return 0;
}

PCL void OnTerminate()
{
	for (int i = 0; i < RE_COUNT; i++)
	{
		if (scan.re[i])
			cleanup_dre2(scan.re[i]);
	}
}

/**
 * @brief Callback used to obtain information about the plugin
 * Memory pointed by info is allocated by the server binary.
 */
PCL void OnInfoRequest(pluginInfo_t *info)
{ 
	// =====  MANDATORY FIELDS  =====
	info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
	info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR; // Requested handler version

	// =====  OPTIONAL  FIELDS  =====
	info->pluginVersion.major = 1;
	info->pluginVersion.minor = 0;
	strncpy(info->fullName, "antiadvert", sizeof(info->fullName));
	strncpy(info->shortDescription, "antiadvert plugin adds function to check if a string message is an advertisement.", sizeof(info->shortDescription));
	strncpy(info->longDescription, "antiadvert plugin adds function to check if a string message is an advertisement.", sizeof(info->longDescription));
}
