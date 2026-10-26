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

## Branches

`setup/structure` collects all branches for review and continued integration.
`main` is unchanged. The independent base branches contain their own bus only,
in addition to the shared structure and pre-existing main tree.

| Branch | Required feature/base branches |
| --- | --- |
| `mod/i2c/base` | `setup/base` |
| `mod/spi/base` | `setup/base` |
| `mod/uart/base` | `setup/base` |
| `mod/i2s/base` | `setup/base` |
| `mod/pwm/base` | `setup/base` |
| `mod/gpio/base` | `setup/base` |
| `mod/i2c/ioExpander` | `mod/i2c/base` |
| `mod/i2c/touchScreen` | `mod/i2c/base` |
| `mod/i2c/rtc` | `mod/i2c/base` |
| `mod/i2c/amplifier` | `mod/i2c/ioExpander` |
| `mod/i2s/audioCodec` | `mod/i2c/base`, `mod/i2s/base` |
| `mod/spi/lcd` | `mod/spi/base`, `mod/gpio/base` |
| `mod/pwm/backlight` | `mod/pwm/base`, `mod/gpio/base` |
| `mod/lvgl_port` | `mod/spi/lcd`, `mod/pwm/backlight`, `mod/i2c/touchScreen` |

## Implementation state

- `components/bsp/i2c/i2cBSP.c`: existing authored implementation; compiled.
- `components/lcd_bl_pwm_bsp/lcd_bl_pwm_bsp.c`: existing implementation; unchanged.
- `components/bsp/touch/axs15231b.c`: exact WIP draft; not compiled. It still has
  an invalid device-config initializer, old I2C names and LVGL 8 callback types.
- `components/lvgl_port/lvgl_port.c`: exact original port draft; not compiled.
- New SPI, UART, I2S, PWM, GPIO, IO expander, RTC, codec, amplifier and LCD APIs:
  declarations only, with no generated `.c` files or inline implementations.
- Empty `.c` placeholders from the WIP were not carried into the split branches.
  Empty files already on `main` were left alone.
- `ns4150b.h` uses the amplifier's name consistently; the empty WIP file
  `ns41540b.h` was not carried forward.

Headers that declare planned APIs must not be called until their C implementation
has been written. Implemented APIs are not simulated by success-returning stubs.
Once an implementation is ready, add its file explicitly to its component's
`SRCS`. CMake currently exposes the unfinished modules as interface libraries.

## Updating dependencies

The branches have linear histories. Multiple required bases are stacked by
rebasing the consumer branch onto each dependency before adding its own work.
Rebased copies can have different SHAs; equivalent patches are still dependencies.
After changing a base, update all consumers in table order and check the result.
For example, on the codec branch:

```sh
git switch mod/i2s/audioCodec
git rebase mod/i2c/base
git rebase mod/i2s/base
git cherry mod/i2s/audioCodec mod/i2c/base
git cherry mod/i2s/audioCodec mod/i2s/base
```

Both `git cherry` checks should have no `+` entries. Review and resolve conflicts
in context; do not discard a base's changes to make the rebase finish.

Back up the current tip before replacing previously rebased dependency commits.
If an upstream history is rewritten, use the old/new dependency boundaries with
`git rebase --onto` rather than treating old copied commits as new feature work.

## Hardware scope

- Touch AXS15231B: dedicated I2C bus.
- LCD AXS15231B: QSPI and direct reset GPIO in the current project wiring;
  backlight has its own PWM branch.
- ES8311 audio codec: I2C control plus I2S audio data.
- NS4150B amplifier: TCA9554 enable bit 7, as used by the audio example.
- PCF85063 RTC: system I2C bus; interrupt routing is left to application wiring.

The RTC header represents alarm comparisons in seconds/minutes/hours/day/weekday;
disabled comparisons use negative values. Calendar data is binary, not BCD.

## Validation

Checked with ESP-IDF 5.4.4 and the existing manifest, which resolved LVGL 9.6.0~1
and esp_lcd_axs15231b 1.0.1~1 in the validation environment.

- All 25 declared dependency edges across the 16 work branches have equivalent
  patches present; the integration branch includes every work branch.
- All application/component C blobs match the original main, WIP or LVGL draft.
- CMake configuration and generation complete successfully.
- All 18 added or changed headers compile individually as C17 and C++17 with
  the ESP32-S3 toolchain. Existing LVGL configuration deprecation `#warning`
  messages remain warnings; no project header errors were suppressed.
- The existing I2C and backlight C sources compile to objects with the generated
  ESP-IDF compile commands.
- Application compilation still stops at `main/main.c:20`, because it includes
  the removed `i2c_bsp.h`. A full firmware build and hardware test are not claimed.

The isolated validation environment needed a process-ID fallback in its installed
component manager because `/proc` did not expose its process namespace. This
environment workaround is not a change to the project or its SDK source.
