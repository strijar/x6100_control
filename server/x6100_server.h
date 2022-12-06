/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Aether Xiegu X6100 Control
 *
 *  Copyright (c) 2022 Belousov Oleg aka R1CBU
 *  Copyright (c) 2022 Rui Oliveira aka CT7ALW
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
