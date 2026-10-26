#pragma once

#include <stdint.h>

#include "i2cBSP.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The existing C file is an unfinished draft; it is preserved without changes. */
typedef struct
{
    uint16_t x;
    uint16_t y;
    uint8_t contactCount;
} touchPanelData_t;

/* Existing draft names and signature are kept. */
extern i2c_master_bus_handle_t touchPanelBusHandle;
extern i2c_master_dev_handle_t disp_touch_dev_handle;
extern void touchPanelInit(void);

/* Planned read API: raw panel coordinates, with no LVGL rotation or queue handling. */
extern esp_err_t touchPanelRead(touchPanelData_t *data);

#ifdef __cplusplus
}
#endif
