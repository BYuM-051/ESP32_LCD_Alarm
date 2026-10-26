#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "tca9554.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
/* Audio example enables the amplifier through TCA9554 bit 7. */
#define AMPLIFIER_ENABLE_PIN_MASK (1u << 7)

/* Initialize the IO expander before this module. No I2S data goes through the amplifier API. */
extern bool amplifierInit(uint8_t enablePinMask, bool activeHigh);
extern esp_err_t amplifierEnable(bool enabled);

#ifdef __cplusplus
}
#endif
