/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Aether Xiegu X6100 Control
 *
 *  Copyright (c) 2022 Belousov Oleg a.k.a. R1CBU
 *  Copyright (c) 2022 Rui Oliveira a.k.a. CT7ALW
 */

#include "x6100_server.h"
#include <iostream>

void x6100_server::rpc_set_vfo(wampcc::wamp_session& caller, wampcc::call_info info) {
	const wampcc::json_array&	list = info.args.args_list;
	const wampcc::json_object&	dict = info.args.args_dict;

	if (list.size() > 0) {
		auto item = list[0];

        if (item.is_uint8())
        {
            uint8_t vfo = item.as_uint();

            if (vfo == 1 || vfo == 2)
            {
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

    if (list.size() > 0)
    {
        auto item = list[0];

        if (item.is_uint())
        {
            uint32_t x = item.as_uint();

            if (x < 55)
            {
                x6100_control_cmd(x6100_rxvol, x);
				dealer->publish(realm, "set_rxvol", {}, info.args);
				caller.result(info.request_id);
				return;
            }
        }
    }

    caller.call_error(info.request_id, "Invalid param");
}
