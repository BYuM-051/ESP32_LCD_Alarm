#pragma once

#include <stdbool.h>

#include "driver/uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
typedef struct
{
    int txPin;
    int rxPin;
    int rtsPin;
    int ctsPin;
} uartBSPPins_t;

/* Use UART_PIN_NO_CHANGE for unused flow-control pins. Buffer sizes are bytes. */
extern bool uartBSPInit(uart_port_t uartPort, const uart_config_t *config, const uartBSPPins_t *pins, int rxBufferSize, int txBufferSize);
extern esp_err_t uartBSPDeinit(uart_port_t uartPort);

#ifdef __cplusplus
}
#endif
