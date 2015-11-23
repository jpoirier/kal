// Copyright (c) 2015 Joseph D Poirier
// Distributable under the terms of The New BSD License
// that can be found in the LICENSE file.

// Package kalibrate wraps libkalibrate.
//
// Build example
//
// kalibrate go wrapper:
//   $ go build -o kal.a kal.go
//

package kal

/*
#cgo CFLAGS: -Isrc/
#cgo linux LDFLAGS: -L. -lkal
#cgo darwin LDFLAGS: -lkal
#cgo windows LDFLAGS: -L. -lkal -LC:/WINDOWS/system32

#include <stdlib.h>
#include <stdint.h>
#include "libkal.h"
*/
import "C"
import "errors"

// Current version.
var PackageVersion = "v0.1"

type ARFCN int

const (
	GSM850  = C.GSM_850
	GSMR900 = C.GSM_R_900
	GSM900  = C.GSM_900
	GSME900 = C.GSM_E_900
	DCS1800 = C.DCS_1800
	PCS1900 = C.PCS_1900
)

const (
	errNoDevice = iota * -1
	errARFCN
	errUSRPSource
	errC0detect
	errBadFreq
	errTune
	errOffsetDetect
	errSetFreqCorr
	errSetCenterFreq
	errOther = -99
)

var errMap = map[int]error{
	success:          nil,
	errNoDevice:      errors.New("no device"),
	errARFCN:         errors.New("arfcn out of range [GSM_850-PCS_1900]"),
	errUSRPSource:    errors.New("usrp_source"),
	errC0detect:      errors.New("c0_detect error"),
	errBadFreq:       errors.New("bad frequency"),
	errTune:          errors.New("tuning error"),
	errOffsetDetect:  errors.New("offset_detect error"),
	errSetFreqCorr:   errors.New("set_freq_correction error"),
	errSetCenterFreq: errors.New("set_center_freq error"),
	errOther:         errors.New("unknown error"),
}

// Context is the opened device's context.
type Context C.rtlsdr_dev_t

// getError returns a textual error description from errno.
func getError(errno int) error {
	if err, ok := errMap[errno]; ok {
		return err
	}
	return errors.New("unknown error")
}

func Kal(dev *Context, arfcn ARFCN) (ppm double, err error) {
	err = C.kal((*C.rtlsdr_dev_t)(dev), (*C.double)(&ppm), C.int(arfcn))
	return getError[err]
}

func KalWorld() {
	C.kal_world()
}
