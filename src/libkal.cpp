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


int kal(rtlsdr_dev_t *dev, int *ppm, int arfcn) {
	if (!dev)
		return -1;
	if ((PCS_1900 < arfcn) || (arfcn < GSM_850))
		return -2;

	int err;
	int chan = 0;
	unsigned int const decimation = 192;
	long int const fpga_master_clock_freq = 52000000;
	double freq = -1.0;

	// new sdr object
	usrp_source *u = new usrp_source(dev, decimation, fpga_master_clock_freq);
	if (!u) {
		fprintf(stderr, "error: usrp_source\n");
		return -3;
	}

	// save the currently tuned freq
	uint32_t freq_saved = u->get_center_freq();

	// channel detection for the arfcn
	err = c0_detect(u, arfcn, &chan);
	if (err != 0 ) {
		fprintf(stderr, "error: c0_detect\n");
		return -4;
	}

	freq = arfcn_to_freq(chan, &arfcn);
	fprintf(stdio, "tuning to channel: %d\n", chan);
	fprintf(stdio, "tuning to arfcn freq: %f\n", freq);
	if ((2e9 < freq) || (freq < 869e6)) {
		fprintf(stderr, "error: arfcn_to_freq\n");
		return -5;
	}

	if(!u->tune(freq)) {
		fprintf(stderr, "error: tune\n");
		return -6;
	}

	double tuner_error = u->m_center_freq - freq;
	err = offset_detect(u, ppm, 0, tuner_error);
	if (err != 0) {
		fprintf(stderr, "error: offset_detect\n");
		return -7;
	}

	if(u->set_freq_correction(*ppm) < 0) {
		fprintf(stderr, "error: set_freq_correction\n");
		return -8;
	}

	err = u->set_center_freq(freq_saved);
	if (err != 0) {
		fprintf(stderr, "error: set center freq\n");
		return -9;
	}

	return 0;
}
