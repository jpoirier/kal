// Copyright (c) 2015 Joseph D Poirier
// Distributable under the terms of The New BSD License
// that can be found in the LICENSE file.

// Package kalibrate wraps libkalibrate.
//
// Build example
//
// kalibrate go wrapper:
//   $ go build -o kalibrate.a kalibrate.go
//

package kalibrate

/*
#cgo CFLAGS: -Isrc
#cgo linux LDFLAGS: -lkal
#cgo darwin LDFLAGS: -lkal
#cgo windows LDFLAGS: -L. -lkal -LC:/WINDOWS/system32

#include <stdlib.h>
#include <stdint.h>
#include "libkal.h"
*/
import "C"

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

// Context is the opened device's context.
type Context C.rtlsdr_dev_t

func Kal(dev *Context, arfcn ARFCN) {
	C.kal((*C.rtlsdr_dev_t)(dev), C.int(arfcn))
}

func KalWorld() {
	C.kal_world()
}
