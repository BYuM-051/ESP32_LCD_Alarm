#include <stdio.h>
#include <stdlib.h>

#include "user_config.h"
#include "freertos/FreeRTOS.h"

#include "i2cBSP.h"
#include "allPins.h"

i2c_master_bus_handle_t i2c1_BusHandle = NULL;

#define TAG "[i2c_bsp.c] "

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

bool i2cB2PInit(i2c_port_num_t i2cPort)
{
    i2cBusConfig.i2c_port = i2cPort;
    if(i2c_new_master_bus(&i2cBusConfig, &i2c1_BusHandle) != ESP_OK)
    {
        return false;
    }
    return true;
}

esp_err_t i2c_writr_buff(i2c_master_dev_handle_t dev_handle,int reg,uint8_t *buf,uint8_t len)
{
    uint8_t *pbuf = NULL;
    esp_err_t ret = i2c_master_bus_wait_all_done(i2c1_BusHandle,i2c_done_pdMS_TICKS);
    if(ret != ESP_OK)
    return ret;
    if(reg == -1)
    {
        ret = i2c_master_transmit(dev_handle,buf,len,i2c_data_pdMS_TICKS);
    }
    else
    {
        pbuf = (uint8_t*)malloc(len+1);
        if(pbuf == NULL)
        {
            return ESP_ERR_NO_MEM;
        }

        pbuf[0] = reg;
        for(uint8_t i = 0; i<len; i++)
        {
            pbuf[i+1] = buf[i];
        }
        ret = i2c_master_transmit(dev_handle,pbuf,len+1,i2c_data_pdMS_TICKS);
        free(pbuf);
        pbuf = NULL;
    }
    return ret;
}
esp_err_t i2c_master_write_read_dev(i2c_master_dev_handle_t dev_handle,uint8_t *writeBuf,uint8_t writeLen,uint8_t *readBuf,uint8_t readLen)
{
    esp_err_t ret = i2c_master_bus_wait_all_done(i2c1_BusHandle, i2c_done_pdMS_TICKS);
    if(ret != ESP_OK)
    return ret;
    ret = i2c_master_transmit_receive(dev_handle,writeBuf,writeLen,readBuf,readLen,i2c_data_pdMS_TICKS);
    return ret;
}
esp_err_t i2c_read_buff(i2c_master_dev_handle_t dev_handle,int reg,uint8_t *buf,uint8_t len)
{
    uint8_t addr = 0;
    esp_err_t ret = i2c_master_bus_wait_all_done(i2c1_BusHandle, i2c_done_pdMS_TICKS);
    if(ret != ESP_OK)
    return ret;
    if(reg == -1)
    {ret = i2c_master_receive(dev_handle, buf,len, i2c_data_pdMS_TICKS);}
    else
    {addr = (uint8_t)reg; ret = i2c_master_transmit_receive(dev_handle,&addr,1,buf,len,i2c_data_pdMS_TICKS);}
    return ret;
}


