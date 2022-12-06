/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Aether Xiegu X6100 Control
 *
 *  Copyright (c) 2022 Belousov Oleg a.k.a. R1CBU
 *  Copyright (c) 2022 Rui Oliveira a.k.a. CT7ALW
 */

#include <unistd.h>
#include <stdio.h>

#include "x6100_flow.h"

int main() {
	if (!x6100_flow_init())
		return 1;

	while (true) {
		x6100_flow_t *pack = x6100_flow_read();

        if (pack)
        {
            printf("tx=%d "
                   "txpwr=%.1f swr=%.1f alc=%.1f vext=%.1f vbat=%.1f bat=%d CRC=%08X\n",
                   pack->flag.tx, pack->tx_power * 0.1, pack->vswr * 0.1f, pack->alc_level * 0.1,
                   pack->vext * 0.1f, pack->vbat * 0.1f, pack->batcap, pack->crc);
        }
    }
}
