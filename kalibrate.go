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
#cgo linux LDFLAGS: -lkalibrate -lm
#cgo darwin LDFLAGS: -lkalibrate -lm
#cgo windows CFLAGS: -IC:/WINDOWS/system32
#cgo windows LDFLAGS: -L. -lkalibrate -LC:/WINDOWS/system32

#include <stdlib.h>
#include <stdint.h>
#include "../src/libkal.h"
*/
import "C"

// Current version.
var PackageVersion = "v0.1"

func Kalibrate() {
	C.kalibrate()
}
