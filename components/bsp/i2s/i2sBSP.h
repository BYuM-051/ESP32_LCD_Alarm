#pragma once

#include <stdbool.h>

#include "driver/i2s_std.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
/* txHandle or rxHandle may be NULL for a one-way stream. Created channels are stopped. */
extern bool i2sBSPInit(const i2s_chan_config_t *channelConfig, const i2s_std_config_t *standardConfig, i2s_chan_handle_t *txHandle, i2s_chan_handle_t *rxHandle);
extern esp_err_t i2sBSPStart(i2s_chan_handle_t channelHandle);
extern esp_err_t i2sBSPStop(i2s_chan_handle_t channelHandle);
extern esp_err_t i2sBSPDeinit(i2s_chan_handle_t channelHandle);

#ifdef __cplusplus
}
#endif
