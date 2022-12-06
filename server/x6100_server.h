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
#include "wampcc/wampcc.h"

extern "C" {
	#include "x6100_control.h"
	#include "x6100_gpio.h"
	#include "x6100_flow.h"
}

class x6100_server {
public:
	x6100_server();
	~x6100_server();

	std::future<void>& shutdown() { return shutdown_future; }
	void flow_pack(const x6100_flow_t *pack);

private:
  	std::string  							realm;

  	std::unique_ptr<wampcc::kernel>    		kernel;
 	std::shared_ptr<wampcc::wamp_router> 	dealer;
 	std::promise<void> 						shutdown_pomise;
  	std::future<void>  						shutdown_future;

	void rpc_set_vfo(wampcc::wamp_session& caller, wampcc::call_info info);
	void rpc_set_rxvol(wampcc::wamp_session& caller, wampcc::call_info& info);
};

