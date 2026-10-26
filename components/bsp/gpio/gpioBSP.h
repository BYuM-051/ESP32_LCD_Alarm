#pragma once

#include <stdbool.h>

#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
extern bool gpioBSPInit(const gpio_config_t *config);
extern esp_err_t gpioBSPWrite(gpio_num_t pin, bool level);
extern esp_err_t gpioBSPRead(gpio_num_t pin, bool *level);

#ifdef __cplusplus
}
#endif
