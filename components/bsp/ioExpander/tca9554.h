#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "i2cBSP.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
#define TCA9554_DEFAULT_ADDRESS 0x20u

/* Pin arguments are 8-bit masks. A set direction bit means input, matching the chip. */
extern bool ioExpanderInit(i2c_master_bus_handle_t busHandle, uint8_t deviceAddress, uint32_t clockHz);
extern esp_err_t ioExpanderSetDirection(uint8_t pinMask, bool input);
extern esp_err_t ioExpanderSetPolarity(uint8_t pinMask, bool inverted);
extern esp_err_t ioExpanderWrite(uint8_t pinMask, uint8_t levels);
extern esp_err_t ioExpanderRead(uint8_t *levels);
extern esp_err_t ioExpanderDeinit(void);

#ifdef __cplusplus
}
#endif
