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

int main() {
	if (!x6100_control_init())
		return 1;

	x6100_control_cmd(x6100_sple_atue_trx, x6100_iptt);
	sleep(1);
	x6100_control_cmd(x6100_sple_atue_trx, 0);
}
