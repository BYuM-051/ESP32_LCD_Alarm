#pragma once

#include <stdbool.h>

#include "spiBSP.h"
#include "gpioBSP.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
/* The caller initializes the QSPI bus and owns its lifetime. Backlight is separate. */
extern bool lcdInit(spi_host_device_t spiHost, gpio_num_t resetPin);
extern esp_lcd_panel_handle_t lcdGetPanelHandle(void);
extern esp_lcd_panel_io_handle_t lcdGetIoHandle(void);
extern esp_err_t lcdSetEnabled(bool enabled);
extern esp_err_t lcdDeinit(void);

#ifdef __cplusplus
}
#endif
