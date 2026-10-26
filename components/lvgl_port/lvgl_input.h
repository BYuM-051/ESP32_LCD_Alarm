#pragma once

#include <stdbool.h>

#include "lvgl.h"
#include "touchPanel.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
extern bool lvglInputInit(lv_display_t *display);
extern lv_indev_t *lvglInputGet(void);

#ifdef __cplusplus
}
#endif
