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

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	bool		resync	: 1;
	bool		tx 		: 1;
	bool		chg		: 1;
	bool		vext	: 1;
	uint32_t			: 28;
} x6100_flow_flags_t;

typedef struct __attribute__((__packed__)) {
	uint32_t			magic;
	float				samples[1024];

	x6100_flow_flags_t	flag;
	uint8_t				reserved_1;
	uint8_t				tx_power;
	uint8_t				vswr;
	uint8_t				alc_level;
	uint8_t				vext;
	uint8_t				vbat;
	uint8_t				batcap;
	uint8_t				reserved_2;
	uint32_t			atu_params;
	uint32_t			reserved_3[4];

	uint32_t			crc;
} x6100_flow_t;

/* Functions */

bool x6100_flow_init();
x6100_flow_t * x6100_flow_read();
