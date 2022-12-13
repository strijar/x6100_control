/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Aether Xiegu X6100 Control
 *
 *  Copyright (c) 2022 Belousov Oleg aka R1CBU
 *  Copyright (c) 2022 Rui Oliveira aka CT7ALW
 */

#pragma once

#include "aether_x6100/control/api.h"

#include <stdbool.h>
#include <stdint.h>

extern int x6100_pin_wifi;
extern int x6100_pin_rf;
extern int x6100_pin_light;

AETHERX6100CTR_API bool x6100_gpio_init();
AETHERX6100CTR_API void x6100_gpio_set(int pin, int value);
