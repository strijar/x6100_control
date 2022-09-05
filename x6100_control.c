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

#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "x6100_control.h"

static int	i2c_fd = 0;
static int	i2c_addr = 0x72;

typedef struct __attribute__((__packed__)) {
	uint16_t	addr;
	uint32_t	arg;
} cmd_struct_t;

/* * */

bool x6100_control_init() {
	i2c_fd = open("/dev/i2c-0", O_RDWR);
	
	return (i2c_fd > 0);
}

bool x6100_control_cmd(x6100_cmd_enum_t cmd, uint32_t arg) {
	cmd_struct_t				command;
  	struct i2c_msg				message = { i2c_addr, 0, sizeof(command), &command };
  	struct i2c_rdwr_ioctl_data	ioctl_data = { &message, 1 };
  	uint16_t					addr = cmd * 4;
  	
  	command.addr = (addr & 0xFF) << 8 | (addr >> 8);
  	command.arg = arg;
  	
  	int res = ioctl(i2c_fd, I2C_RDWR, &ioctl_data);
  	
  	return (res > 0);
}
