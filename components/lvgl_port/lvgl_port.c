#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "esp_timer.h"

#include "lvgl_port.h"


static SemaphoreHandle_t lvglMutex= NULL;

static uint32_t lvglGetTick(void);
static void lvglPortTask(void *arg);

