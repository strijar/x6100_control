/*
 *  Xiegu X6100 Control interface
 *  Copyright (c) 2022 by Belousov Oleg aka R1CBU
 *
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <unistd.h>

#include <x6100control/x6100_control.h>
#include <x6100control/x6100_flow.h>
#include <x6100control/x6100_gpio.h>

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
		
		if (pack) {
			printf(
				"tx=%d "
				"txpwr=%.1f swr=%.1f alc=%.1f vext=%.1f vbat=%.1f bat=%d atu_params=%08X\n", 
				pack->flag.tx,
				pack->tx_power * 0.1, pack->vswr * 0.1f, pack->alc_level * 0.1, pack->vext * 0.1f, pack->vbat * 0.1f, pack->batcap,
				pack->atu_params
			);

			switch (atu) {
				case ATU_IDLE:
					x6100_control_cmd(x6100_sple_atue_trx, x6100_atu_tune);
					x6100_gpio_set(x6100_pin_light, 1);
					atu = ATU_START;
					break;
					
				case ATU_START:
					if (pack->flag.tx) {
						atu = ATU_RUN;
					}
					break;
					
				case ATU_RUN:
					if (!pack->flag.tx) {
						x6100_control_cmd(x6100_sple_atue_trx, 0);
						x6100_gpio_set(x6100_pin_light, 0);
						atu = ATU_DONE;
					}
					break;
			}
		}
	}
}
