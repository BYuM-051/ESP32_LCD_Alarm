#include "touchPanel.h"

#include "i2cBSP.h"

i2c_master_bus_handle_t touchPanelBusHandle = NULL;

static const i2c_device_config_t touchPanelDeviceConfig = 
{
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .scl_speed_hz = 300000,
    .device_address = 0x3B
};

static void touchPanelTask(void *arg);

void touchPanelInit(void)
{
    i2c_device_config_t dev_cfg = 
    {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .scl_speed_hz = 300000,
        .device_address = DISP_TOUCH_ADDR;
    };

    ESP_ERROR_CHECK(i2c_master_bus_add_device(touchPanelBusHandle, &dev_cfg, &disp_touch_dev_handle));

}

uint8_t i2c_master_touch_write_read(i2c_master_dev_handle_t dev_handle,uint8_t *writeBuf,uint8_t writeLen,uint8_t *readBuf,uint8_t readLen)
{
    uint8_t ret;
    ret = i2c_master_bus_wait_all_done(user_i2c_port1_handle,i2c_done_pdMS_TICKS);
    if(ret != ESP_OK)
    return ret;
    ret = i2c_master_transmit_receive(dev_handle,writeBuf,writeLen,readBuf,readLen,i2c_data_pdMS_TICKS);
    return ret;
}

static void touchPanelTask(void *arg)
{
    
}

static void example_lvgl_touch_cb(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
  //static uint8_t read_touchpad_cmd[8] = {0xb5, 0xab, 0xa5, 0x5a, 0x0, 0x0, 0x0, 0x8};
  uint8_t read_touchpad_cmd[11] = {0xb5, 0xab, 0xa5, 0x5a, 0x0, 0x0, 0x0, 0x0e,0x0, 0x0, 0x0};
  uint8_t buff[32] = {0};
  memset(buff,0,32);
  ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_write_read_dev(disp_touch_dev_handle,read_touchpad_cmd,11,buff,32));
  uint16_t pointX;
  uint16_t pointY;
  pointX = (((uint16_t)buff[2] & 0x0f) << 8) | (uint16_t)buff[3];
  pointY = (((uint16_t)buff[4] & 0x0f) << 8) | (uint16_t)buff[5];
  //ESP_LOGI("Touch","%d,%d",buff[0],buff[1]);
  if (buff[1]>0 && buff[1]<5)
  {
    data->state = LV_INDEV_STATE_PR;
    if(pointX > EXAMPLE_LCD_V_RES) pointX = EXAMPLE_LCD_V_RES;
    if(pointY > EXAMPLE_LCD_H_RES) pointY = EXAMPLE_LCD_H_RES;
    data->point.x = pointY;
    data->point.y = (EXAMPLE_LCD_V_RES-pointX);
	/*touch test*/
	app_touch_t user_touch_data;
	user_touch_data.x = data->point.x;
	user_touch_data.y = data->point.y;
    xQueueSend(app_touch_data_queue,&user_touch_data,0);
  }
  else 
  {
    data->state = LV_INDEV_STATE_REL;
  }
}
