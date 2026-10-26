#include <stdlib.h>
#include <string.h>

#include "esp_log.h"

#include "i2cBSP.h"
#include "allPins.h"

#define TAG "[i2cBSP.c] "

i2c_master_bus_handle_t i2c1_BusHandle = NULL;

static const int i2cTransferTimeoutMs = 1000;

static i2c_master_bus_config_t i2cBusConfig =
{
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .scl_io_num = PIN_I2C_SCL,
    .sda_io_num = PIN_I2C_SDA,
    .glitch_ignore_cnt = 7,
    .flags =
    {
        .enable_internal_pullup = true
    }
};

bool i2cBSPInit(i2c_port_num_t i2cPort)
{
    if(i2c1_BusHandle != NULL)
    {
        ESP_LOGW(TAG, "%s: Bus already initialized", __func__);
        return false;
    }

    i2cBusConfig.i2c_port = i2cPort;

    esp_err_t ret = i2c_new_master_bus(&i2cBusConfig, &i2c1_BusHandle);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: %s", __func__, esp_err_to_name(ret));
        return false;
    }

    ESP_LOGI(TAG, "Bus initialized: port=%d, SCL=%d, SDA=%d", (int)i2cPort, (int)i2cBusConfig.scl_io_num, (int)i2cBusConfig.sda_io_num);

    return true;
}

esp_err_t i2c_writr_buff(i2c_master_dev_handle_t devHandle, int reg, const uint8_t *buf, uint8_t len)
{
    if(devHandle == NULL || buf == NULL || len == 0 || reg < -1 || reg > UINT8_MAX)
    {
        ESP_LOGE(TAG, "%s: Invalid argument", __func__);
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret;

    if(reg == -1)
    {
        ret = i2c_master_transmit(devHandle, buf, len, i2cTransferTimeoutMs);
    }
    else
    {
        size_t transferLen = (size_t)len + 1;
        uint8_t *transferBuf = malloc(transferLen);
        if(transferBuf == NULL)
        {
            ESP_LOGE(TAG, "%s: Buffer allocation failed", __func__);
            return ESP_ERR_NO_MEM;
        }

        transferBuf[0] = (uint8_t)reg;
        memcpy(&transferBuf[1], buf, len);

        ret = i2c_master_transmit(devHandle, transferBuf, transferLen, i2cTransferTimeoutMs);

        free(transferBuf);
    }

    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: reg=%d, len=%u, %s", __func__, reg, (unsigned int)len, esp_err_to_name(ret));
    }

    return ret;
}

esp_err_t i2c_master_write_read_dev(i2c_master_dev_handle_t devHandle, const uint8_t *writeBuf, uint8_t writeLen, uint8_t *readBuf, uint8_t readLen)
{
    if(devHandle == NULL || writeBuf == NULL || readBuf == NULL || writeLen == 0 || readLen == 0)
    {
        ESP_LOGE(TAG, "%s: Invalid argument", __func__);
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret = i2c_master_transmit_receive(devHandle, writeBuf, writeLen, readBuf, readLen, i2cTransferTimeoutMs);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: writeLen=%u, readLen=%u, %s", __func__, (unsigned int)writeLen, (unsigned int)readLen, esp_err_to_name(ret));
    }

    return ret;
}

esp_err_t i2c_read_buff(i2c_master_dev_handle_t devHandle, int reg, uint8_t *buf, uint8_t len)
{
    if(devHandle == NULL || buf == NULL || len == 0 || reg < -1 || reg > UINT8_MAX)
    {
        ESP_LOGE(TAG, "%s: Invalid argument", __func__);
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret;

    if(reg == -1)
    {
        ret = i2c_master_receive(devHandle, buf, len, i2cTransferTimeoutMs);
    }
    else
    {
        uint8_t addr = (uint8_t)reg;

        ret = i2c_master_transmit_receive(devHandle, &addr, sizeof(addr), buf, len, i2cTransferTimeoutMs);
    }

    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "%s: reg=%d, len=%u, %s", __func__, reg, (unsigned int)len, esp_err_to_name(ret));
    }

    return ret;
}