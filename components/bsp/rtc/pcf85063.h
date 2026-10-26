#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "i2cBSP.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
#define PCF85063_ADDRESS 0x51u

typedef struct
{
    uint16_t year;     /* 2000..2099 */
    uint8_t month;     /* 1..12 */
    uint8_t day;       /* 1..31 */
    uint8_t weekday;   /* 0..6 */
    uint8_t hour;      /* 0..23 */
    uint8_t minute;    /* 0..59 */
    uint8_t second;    /* 0..59 */
} rtcTime_t;

/* A negative alarm field disables that comparison. All values use binary, not BCD. */
typedef struct
{
    int8_t second;
    int8_t minute;
    int8_t hour;
    int8_t day;
    int8_t weekday;
} rtcAlarm_t;

extern bool rtcInit(i2c_master_bus_handle_t busHandle, uint32_t clockHz);
extern esp_err_t rtcGetTime(rtcTime_t *time, bool *oscillatorStopped);
extern esp_err_t rtcSetTime(const rtcTime_t *time);
extern esp_err_t rtcSetAlarm(const rtcAlarm_t *alarm, bool interruptEnabled);
extern esp_err_t rtcGetAlarmPending(bool *pending);
extern esp_err_t rtcClearAlarm(void);
extern esp_err_t rtcDeinit(void);

#ifdef __cplusplus
}
#endif
