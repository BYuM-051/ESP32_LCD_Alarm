#pragma once

#include <stdbool.h>

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Public interface for the existing, unfinished LVGL port draft. */
extern bool lvglPortInit(void);
extern bool lvglPortStart(void);
/* timeoutMs == -1 waits indefinitely. */
extern bool lvglLock(int timeoutMs);
extern void lvglUnlock(void);

#ifdef __cplusplus
}
#endif
