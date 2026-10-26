#pragma once

#include <stdbool.h>

#include "lvgl.h"
#include "axs15231bLcd.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
extern bool lvglDisplayInit(esp_lcd_panel_handle_t panelHandle, esp_lcd_panel_io_handle_t ioHandle);
extern lv_display_t *lvglDisplayGet(void);

#ifdef __cplusplus
}
#endif
