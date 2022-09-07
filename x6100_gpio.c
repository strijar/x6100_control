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
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "x6100_gpio.h"

int x6100_pin_wifi;
int x6100_pin_rf;
int x6100_pin_light;

static int gpio_open_value(uint16_t pin) {
	char	str[64];
	int		fd, len;

	snprintf(str, sizeof(str), "/sys/class/gpio/gpio%i/value", pin);

	return open(str, O_RDWR);
}

static bool gpio_create(uint16_t pin) {
	char	str[64];
	int		fd, len;
	
	len = snprintf(str, sizeof(str), "%i\n", pin);
	fd = open("/sys/class/gpio/export", O_WRONLY);

	if (fd < 0) 
		return false;
		
	if (write(fd, str, len) < 0) {
		close(fd);
		return false;
	}
		
	close(fd);

	snprintf(str, sizeof(str), "/sys/class/gpio/gpio%i/direction", pin);
	fd = open(str, O_WRONLY);
	
	if (fd < 0)
		return false;

	if (write(fd, "out\n", 4) < 0) {
		close(fd);
		return false;
	}

	close(fd);
	return true;
}

static int gpio_open(uint16_t pin) {
	int fd = gpio_open_value(pin);
	
	if (fd < 0) {
		if (gpio_create(pin)) {
			fd = gpio_open_value(pin);
		} else {
			fd = -1;
		}
	}

	return fd;
}

bool x6100_gpio_init() {
	x6100_pin_wifi = gpio_open(357);
	x6100_pin_rf = gpio_open(138);
	x6100_pin_light = gpio_open(143);
	
	return (x6100_pin_wifi > 0) && (x6100_pin_rf > 0) && (x6100_pin_light > 0);
}

void x6100_gpio_set(int pin, int value) {
	char	str[8];
	
	int len = snprintf(str, sizeof(str), "%i\n", value);
	write(pin, str, len);
}
