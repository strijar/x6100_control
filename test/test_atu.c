/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Aether Xiegu X6100 Control
 *
 *  Copyright (c) 2022 Belousov Oleg a.k.a. R1CBU
 *  Copyright (c) 2022 Rui Oliveira a.k.a. CT7ALW
 */

#include <unistd.h>

#include "x6100_control.h"
#include "x6100_flow.h"
#include "x6100_gpio.h"

typedef enum {
	ATU_IDLE = 0,
	ATU_START,
	ATU_RUN,
	ATU_DONE
} atu_status_t;

int main() {
	atu_status_t atu = ATU_IDLE;

	if (!x6100_control_init())
		return 1;

	if (!x6100_flow_init())
		return 1;

	if (!x6100_gpio_init())
		return 1;

	x6100_control_cmd(x6100_vfoa_freq, 7135000);

	while (atu != ATU_DONE) {
		x6100_flow_t *pack = x6100_flow_read();

        if (pack)
        {
            printf("tx=%d "
                   "txpwr=%.1f swr=%.1f alc=%.1f vext=%.1f vbat=%.1f bat=%d atu_params=%08X\n",
                   pack->flag.tx, pack->tx_power * 0.1, pack->vswr * 0.1f, pack->alc_level * 0.1,
                   pack->vext * 0.1f, pack->vbat * 0.1f, pack->batcap, pack->atu_params);

            switch (atu)
            {
            case ATU_IDLE:
                x6100_control_cmd(x6100_sple_atue_trx, x6100_atu_tune);
                x6100_gpio_set(x6100_pin_light, 1);
                atu = ATU_START;
                break;

            case ATU_START:
                if (pack->flag.tx)
                {
                    atu = ATU_RUN;
                }
                break;

            case ATU_RUN:
                if (!pack->flag.tx)
                {
                    x6100_control_cmd(x6100_sple_atue_trx, 0);
                    x6100_gpio_set(x6100_pin_light, 0);
                    atu = ATU_DONE;
                }
                break;
            }
        }
    }
}
