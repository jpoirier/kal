/*
 * Copyright (c) 2015, Joseph Poirier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     *  Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     *  Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <rtl-sdr.h>
#include "kal.h"
#include "libkal.h"
#include "arfcn_enums.h"
#include "rtlsdr_source.h"



int kal(rtlsdr_dev_t *dev, int arfcn) {
	if (!dev)
		return -1;
	if (arfcn < GSM_850 || arfcn > PCS_1900)
		return -2;

	int err;
	int hz_adjust = 0;
	unsigned int const decimation = 192;
	long int const fpga_master_clock_freq = 52000000;
	double freq = 0.0;
	double power = 0.0;

	// TODO: save the devices current settings
	usrp_source *u = new usrp_source(dev, decimation, fpga_master_clock_freq);
	if(!u) {
		fprintf(stderr, "error: usrp_source\n");
		return -3;
	}

	err = c0_detect(u, arfcn, &freq, &power);
	if (err != 0 && freq == 0.0)
		return -4;

	if((freq < 869e6) || (2e9 < freq)) {
		fprintf(stderr, "error: bad frequency: %lf\n", freq);
		return -5;
	}

	if(!u->tune(freq+hz_adjust)) {
		fprintf(stderr, "error: usrp_source::tune\n");
		return -6;
	}

	double tuner_error = u->m_center_freq - freq;
	err = offset_detect(u, hz_adjust, tuner_error);
	if (err != 0) {
		fprintf(stderr, "error: offset_detect\n");
		return -7;
	}

	// TODO: reset devices previous settings
	return 0;
}

#define ARFCN_CNT (6)
static int const freqs[ARFCN_CNT] = {GSM_850, GSM_900, GSM_R_900, GSM_E_900, DCS_1800, PCS_1900};

void kal_world(void) {
	int i;
	int cnt;
	int err;
	int hz_adjust = 0;
	unsigned int const decimation = 192;
	long int const fpga_master_clock_freq = 52000000;
	double freq = 0.0;
	double power = 0.0;

	cnt = rtlsdr_get_device_count();
	for (i = 0; i < cnt; i++) {
		usrp_source *u = new usrp_source(decimation, fpga_master_clock_freq);

		if(!u) {
			fprintf(stderr, "error: usrp_source\n");
			continue;
		}
		if(u->open(i) == -1) {
			fprintf(stderr, "error: usrp_source::open\n");
			continue;
		}

		for (int i = 0; i < ARFCN_CNT; i++) {
			err = c0_detect(u, freqs[i], &freq, &power);
			if (err != 0 && freq == 0.0)
				continue;
			break;
		}

		if((freq < 869e6) || (2e9 < freq)) {
			fprintf(stderr, "error: bad frequency: %lf\n", freq);
			continue;
		}

		if(!u->tune(freq+hz_adjust)) {
			fprintf(stderr, "error: usrp_source::tune\n");
			continue;
		}

		double tuner_error = u->m_center_freq - freq;
		err = offset_detect(u, hz_adjust, tuner_error);
		if (err != 0)
			fprintf(stderr, "error: offset_detect\n");
	}
}
