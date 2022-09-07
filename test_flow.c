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

#include "x6100_flow.h"

int main() {
	if (!x6100_flow_init())
		return 1;

	while (true) {
		x6100_flow_t *pack = x6100_flow_read();
		
		if (pack) {
			printf(
				"tx=%d "
				"txpwr=%.1f swr=%.1f alc=%.1f vext=%.1f vbat=%.1f bat=%d CRC=%08X\n", 
				pack->flag.tx,
				pack->tx_power * 0.1, pack->vswr * 0.1f, pack->alc_level * 0.1, pack->vext * 0.1f, pack->vbat * 0.1f, pack->batcap,
				pack->crc
			);
		}
	}
}
