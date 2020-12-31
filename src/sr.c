#include "sr.h"

sr_t sr;

/**
 * @brief
 * SR Initialization from Com_Init()
 */
void SR_Init()
{
    memset(&sr, 0, sizeof(sr));
}
