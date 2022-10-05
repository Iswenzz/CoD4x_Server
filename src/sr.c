#include "sr.h"

sr_t sr;

void SR_Init()
{
    memset(&sr, 0, sizeof(sr));

	SR_Initialize();
}
