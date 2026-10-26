#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "driver/i2c_master.h"

// NOTE: Check allPins.h after modifying pin information.
#define PIN_I2C_SCL GPIO_NUM_18
#define PIN_I2C_SDA GPIO_NUM_17

#ifdef __cplusplus
extern "C" {
#endif

extern i2c_master_bus_handle_t i2c1_BusHandle;

extern bool i2cBSPInit(i2c_port_num_t i2cPort);
extern esp_err_t i2c_writr_buff(i2c_master_dev_handle_t devHandle, int reg, const uint8_t *buf, uint8_t len);
extern esp_err_t i2c_master_write_read_dev(i2c_master_dev_handle_t devHandle, const uint8_t *writeBuf, uint8_t writeLen, uint8_t *readBuf, uint8_t readLen);
extern esp_err_t i2c_read_buff(i2c_master_dev_handle_t devHandle, int reg, uint8_t *buf, uint8_t len);

#ifdef __cplusplus
}
#endif