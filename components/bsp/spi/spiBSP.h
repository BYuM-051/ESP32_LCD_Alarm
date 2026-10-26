#pragma once

#include <stdbool.h>

#include "driver/spi_master.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Planned API. Implementation is intentionally not provided yet. */
extern bool spiBSPInit(spi_host_device_t spiHost, const spi_bus_config_t *busConfig, spi_dma_chan_t dmaChannel);
extern esp_err_t spiBSPDeinit(spi_host_device_t spiHost);

#ifdef __cplusplus
}
#endif
