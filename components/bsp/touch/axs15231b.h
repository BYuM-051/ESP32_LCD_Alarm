#pragma once

#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

extern i2c_master_dev_handle_t disp_touch_dev_handle;

void touchPanelInit(void);

#ifdef __cplusplus
}
#endif