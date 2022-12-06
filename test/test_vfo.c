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
