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

#include <chrono>
#include <iostream>
#include <unistd.h>

#include "x6100_server.h"

using namespace std::chrono;

x6100_server::x6100_server() 
	:
	realm("default"),
    kernel(new wampcc::kernel({}, wampcc::logger::console())),
    dealer(new wampcc::wamp_router(kernel.get(), nullptr)),
    shutdown_future(shutdown_pomise.get_future())
{
	dealer->callable(realm,  "set_vfo", [this](wampcc::wamp_router&, wampcc::wamp_session& ws, wampcc::call_info info) { rpc_set_vfo(ws, info); });
  	dealer->callable(realm,  "set_rxvol", [this](wampcc::wamp_router&, wampcc::wamp_session& ws, wampcc::call_info info) { rpc_set_rxvol(ws, info); });

  	auto fut = dealer->listen(wampcc::auth_provider::no_auth_required(), 55555);

  	if (fut.wait_for(std::chrono::milliseconds(250)) != std::future_status::ready)
		throw std::runtime_error("timeout during router listen");

   	if (auto ec = fut.get())
   		throw std::runtime_error("listen failed: err " + std::to_string(ec.os_value()) + ", " + ec.message());

   	cmd_idle = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

x6100_server::~x6100_server() {
	dealer.reset();
	kernel.reset();
}

void x6100_server::flow_pack(const x6100_flow_t *pack) {
    wampcc::wamp_args tx_args;

    tx_args.args_dict["flag"] = pack->flag.tx;
    tx_args.args_dict["power"] = pack->tx_power * 0.1f;
    tx_args.args_dict["vswr"] = pack->vswr * 0.1f;
    tx_args.args_dict["alc"] = pack->alc_level * 0.1f;

	dealer->publish(realm, "tx", {}, tx_args);

    wampcc::wamp_args power_args;

    power_args.args_dict["ext"] = pack->vext * 0.1f;
    power_args.args_dict["bat"] = pack->vbat * 0.1f;
    power_args.args_dict["capacity"] = pack->batcap;

	dealer->publish(realm, "power", {}, power_args);

	wampcc::wamp_args	samples_args;
	wampcc::json_array	samples_array;

	samples_array.reserve(1024);
	
	for (int i = 0; i < 1024; i++)
		samples_array.push_back(pack->samples[i]);

	samples_args.args_list = samples_array;

	dealer->publish(realm, "samples", {}, samples_args);
}

void x6100_server::idle(bool update) {
	uint64_t now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	if (update) {
		cmd_idle = now;
	} else if (now - cmd_idle > 1000) {
		x6100_control_idle();
		cmd_idle = now;
	}
}

///

int main() {
	if (!x6100_control_init())
		return 1;

	if (!x6100_gpio_init())
		return 1;

	if (!x6100_flow_init())
		return 1;

	try {
    	x6100_server 	server;

		while (true) {
			x6100_flow_t 	*pack = x6100_flow_read();

			if (pack) {
				server.flow_pack(pack);
			} else {
				usleep(10);
			}
			
			server.idle(false);
		}
    	
    	return 0;
  	} catch (std::exception& e) {
  		std::cerr << e.what() << std::endl;
    	return 1;
  	}
}
