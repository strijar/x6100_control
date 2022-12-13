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

typedef struct
{
    bool resync : 1;
    bool tx : 1;
    bool chg : 1;
    bool vext : 1;
    uint32_t : 28;
} x6100_flow_flags_t;

typedef struct __attribute__((__packed__))
{
    uint32_t magic;
    float samples[1024];

    x6100_flow_flags_t flag;
    uint8_t reserved_1;
    uint8_t tx_power;
    uint8_t vswr;
    uint8_t alc_level;
    uint8_t vext;
    uint8_t vbat;
    uint8_t batcap;
    uint8_t reserved_2;
    uint32_t atu_params;
    uint32_t reserved_3[4];

    uint32_t crc;
} x6100_flow_t;

/* Functions */

AETHERX6100CTR_API bool x6100_flow_init();
AETHERX6100CTR_API x6100_flow_t *x6100_flow_read();
