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
#cgo linux LDFLAGS: -L. -lkal -lm
#cgo darwin LDFLAGS: -lkal -lm
#cgo windows LDFLAGS: -L. -lkal -LC:/WINDOWS/system32

#include <stdlib.h>
#include <stdint.h>
#include "libkal.h"
*/
import "C"

// Current version.
var PackageVersion = "v0.1"

func Kalibrate() {
	C.kalibrate()
}
