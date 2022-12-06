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

#include "x6100_control.h"
#include "x6100_gpio.h"

int main() {
	if (!x6100_control_init())
		return 1;

	if (!x6100_gpio_init())
		return 1;

	x6100_control_cmd(x6100_rxvol, 20);
	x6100_control_cmd(x6100_vfoa_mode, x6100_mode_usb_dig);

	while (true) {
		printf("Freq 7.074 MHz\n");
		x6100_control_cmd(x6100_vfoa_freq, 7074000);
		sleep(5);

		printf("Freq 10.100 MHz\n");
		x6100_control_cmd(x6100_vfoa_freq, 10100000);
		sleep(5);

		printf("Freq 14.074 MHz\n");
		x6100_control_cmd(x6100_vfoa_freq, 14074000);
		sleep(5);
	}
}
