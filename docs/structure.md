# ESP32 alarm structure

The existing C implementations are preserved. New modules provide declarations
and CMake registration only; a declared API is not an implemented API.

`setup/base` contains shared BSP pin definitions and nested component discovery.
Each bus base branches from it independently. Device branches contain their
required base commits before their own header/CMake commits.

Existing root application code is still a work in progress. In particular,
the I2C refactor removed `i2c_bsp.h` while `main/main.c` still includes it and
calls `touch_i2c_master_Init()`. Completing that migration requires C changes
and is deliberately outside this structure change.

The current I2C implementation uses the touch pins (SCL 18, SDA 17).
The RTC, codec and IO expander use the other bus (SCL 48, SDA 47).
Their planned init APIs accept a bus handle rather than implicitly using
`i2c1_BusHandle`. Creating that second bus remains implementation work.

The pin definitions follow this repository's existing V1 configuration, not
the newer V2 wiring. Existing `main/user_config.h` remains unchanged.

The original WIP is retained on `backup/wip-20261025`, and the existing LVGL
port draft on `backup/lvgl-port-20261025`.

Reference: ESP-IDF v5.4 build system, configuration-only components:
https://docs.espressif.com/projects/esp-idf/en/release-v5.4/esp32s3/api-guides/build-system.html
