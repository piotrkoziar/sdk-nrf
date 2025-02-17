/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/device.h>
#include <zephyr/sys/printk.h>
#include <dtm.h>

#include "transport/dtm_transport.h"

int main(void)
{
	int err;
	union dtm_tr_packet cmd;
	uint16_t cnt;

	printk("Starting Direct Test Mode sample\n");

	err = dtm_tr_init();
	if (err) {
		printk("Error initializing DTM transport: %d\n", err);
		return err;
	}
	k_sleep(K_MSEC(5000));
	dtm_setup_reset();
	k_sleep(K_MSEC(5000));
	dtm_test_transmit(0x11, 20, DTM_PACKET_55);
	k_sleep(K_MSEC(5000));
	dtm_test_receive(11);
	k_sleep(K_MSEC(5000));
	dtm_test_end(&cnt);
	for (;;) {
		cmd = dtm_tr_get();
		err = dtm_tr_process(cmd);
		if (err) {
			printk("Error processing command: %d\n", err);
			return err;
		}
	}
}
