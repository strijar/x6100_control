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

#include "x6100_server.h"
#include <iostream>

void x6100_server::rpc_set_vfo(wampcc::wamp_session& caller, wampcc::call_info info) {
	const wampcc::json_array&	list = info.args.args_list;
	const wampcc::json_object&	dict = info.args.args_dict;

	dealer->publish(realm, "set_vfo", {}, info.args);
	caller.result(info.request_id);

	if (list.size() > 0) {
		auto item = list[0];
		
		if (item.is_uint8()) {
			uint8_t vfo = item.as_uint();
			
			if (vfo == 1 || vfo == 2) {
				for (auto item = dict.begin(); item != dict.end(); item++) {
					uint32_t x = item->second.as_uint();

					if (item->first.compare("freq") == 0) {
						x6100_control_cmd(vfo == 1 ? x6100_vfoa_freq : x6100_vfob_freq, x);
					} else if (item->first.compare("mode") == 0) {
						if (x >= x6100_mode_lsb && x <= x6100_mode_nfm) {
							x6100_control_cmd(vfo == 1 ? x6100_vfoa_mode : x6100_vfob_mode, x);
						}
					}
				}

				dealer->publish(realm, "set_vfo", {}, info.args);
				caller.result(info.request_id);
				return;
			}
		}
	}
	
	caller.call_error(info.request_id, "Invalid param");
}

void x6100_server::rpc_set_rxvol(wampcc::wamp_session& caller, wampcc::call_info& info) {
	const wampcc::json_array& list = info.args.args_list;
	
	if (list.size() > 0) {
		auto item = list[0];
		
		if (item.is_uint()) {
			uint32_t x = item.as_uint();
			
			if (x < 55) {
				x6100_control_cmd(x6100_rxvol, x);
				dealer->publish(realm, "set_rxvol", {}, info.args);
				caller.result(info.request_id);
				return;
			}
		}
	}
	
	caller.call_error(info.request_id, "Invalid param");
}
