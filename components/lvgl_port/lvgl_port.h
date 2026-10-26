#pragma once

#include "lvgl.h"

extern bool lvglPortInit(void);
extern bool lvglPortStart(void);
extern bool lvglLock(int timeoutMs);
extern void lvglUnlock(void);