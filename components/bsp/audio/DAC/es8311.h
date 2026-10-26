#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "i2cBSP.h"
#include "i2sBSP.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
typedef struct
{
    i2c_master_bus_handle_t controlBus;
    i2s_chan_handle_t txHandle;
    uint8_t deviceAddress;      /* 7-bit I2C address */
    uint32_t controlClockHz;
    uint32_t sampleRateHz;
    uint32_t masterClockHz;
    i2s_data_bit_width_t sampleBits;
} audioCodecConfig_t;

/* The caller owns the I2C bus and I2S channel and must configure matching audio clocks. */
extern bool audioCodecInit(const audioCodecConfig_t *config);
extern esp_err_t audioCodecSetVolume(uint8_t percent); /* 0..100 */
extern esp_err_t audioCodecSetMute(bool muted);
extern esp_err_t audioCodecWrite(const void *samples, size_t bytes, size_t *bytesWritten, uint32_t timeoutMs);
extern esp_err_t audioCodecDeinit(void);

#ifdef __cplusplus
}
#endif
