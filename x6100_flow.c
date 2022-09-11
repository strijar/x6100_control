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
 
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "x6100_flow.h"

#define BUF_SIZE		(sizeof(x6100_flow_t) * 3)

static int				flow_fd;

static uint8_t			*buf = NULL;
static uint8_t			*buf_read = NULL;
static uint16_t			buf_size = 0;

static const uint32_t	magic = 0xAA5555AA;

bool x6100_flow_init() {
	flow_fd = open("/dev/ttyS1", O_RDWR);
	
	if (flow_fd < 0)
		return false;
		
	struct termios attr;
	
	tcgetattr(flow_fd, &attr);
	
    cfsetispeed(&attr, B1152000);
    cfsetospeed(&attr, B1152000);	

	#if 1
	cfmakeraw(&attr);
	#else
	attr.c_cflag = attr.c_cflag & 0xfffffe8f | 0x30;
	attr.c_iflag = attr.c_iflag & 0xfffffa14;
	attr.c_oflag = attr.c_oflag & 0xfffffffa;
	attr.c_lflag = attr.c_lflag & 0xffff7fb4;	
	#endif
    
    if (tcsetattr(flow_fd, 0, &attr) < 0) {
    	close(flow_fd);
    	return false;
    }

	buf = malloc(BUF_SIZE);
	buf_read = buf;
	buf_size = 0;

	return true;    
}

static x6100_flow_t * flow_check() {
	uint8_t *begin = memmem(buf, buf_size, &magic, sizeof(magic));

	if (begin) {
		uint32_t len = buf + buf_size - begin;
		
		if (len >= sizeof(x6100_flow_t)) {
			uint8_t			*tail_ptr = begin + sizeof(x6100_flow_t);
			uint16_t		tail_len = len - sizeof(x6100_flow_t);
			x6100_flow_t	*pack = begin;

			// TODO: check crc32

			memmove(buf, tail_ptr, tail_len);

			buf_read = buf + tail_len;
			buf_size = tail_len;

			return pack;
		}
	}
	
	return NULL;
}

x6100_flow_t * x6100_flow_read() {
	if (buf_size >= BUF_SIZE) {
		buf_size = 0;
		buf_read = buf;
	}

	int res = read(flow_fd, buf_read, BUF_SIZE - buf_size);
	
	if (res > 0) {
		buf_size += res;
		buf_read += res;

		if (buf_size > sizeof(x6100_flow_t)) {
			return flow_check();
		}
	}
	
	return NULL;
}
