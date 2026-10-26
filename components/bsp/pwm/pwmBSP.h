#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "driver/ledc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
/* Duty is the raw timer-resolution value, not a percentage. */
extern bool pwmBSPInit(const ledc_timer_config_t *timerConfig, const ledc_channel_config_t *channelConfig);
extern esp_err_t pwmBSPSetDuty(ledc_mode_t speedMode, ledc_channel_t channel, uint32_t duty);
extern esp_err_t pwmBSPStop(ledc_mode_t speedMode, ledc_channel_t channel, uint32_t idleLevel);

#ifdef __cplusplus
}
#endif
