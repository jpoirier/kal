// +build ignore

package main

import (
	"errors"
	"log"

	rtl "github.com/jpoirier/gortlsdr"
	"github.com/jpoirier/kal"
)

func main() {
	var err error
	var dev *rtl.Context

	//---------- Device Check ----------
	if c := rtl.GetDeviceCount(); c == 0 {
		log.Fatal("No devices found, exiting.\n")
	} else {
		for i := 0; i < c; i++ {
			m, p, s, err := rtl.GetDeviceUsbStrings(i)
			if err == nil {
				err = errors.New("")
			}
			log.Printf("GetDeviceUsbStrings %s - %s %s %s\n",
				err, m, p, s)
		}
	}

	log.Printf("===== Device name: %s =====\n", rtl.GetDeviceName(0))
	log.Printf("===== Running tests using device indx: 0 =====\n")

	//---------- Open Device ----------
	if dev, err = rtl.Open(0); err != nil {
		log.Fatal("\tOpen Failed, exiting\n")
	}
	defer dev.Close()

	//---------- Device Strings ----------
	m, p, s, err := dev.GetUsbStrings()
	if err != nil {
		log.Printf("\tGetUsbStrings Failed - error: %s\n", err)
	} else {
		log.Printf("\tGetUsbStrings - %s %s %s\n", m, p, s)
	}

	log.Printf("\tGetTunerType: %s\n", dev.GetTunerType())

	//---------- Device Info ----------
	info, err := dev.GetHwInfo()
	if err != nil {
		log.Printf("\tGetHwInfo Failed - error: %s\n", err)
	} else {
		log.Printf("\tVendor ID      : 0x%X\n", info.VendorID)
		log.Printf("\tProduct ID     : 0x%X\n", info.ProductID)
		log.Println("\tManufacturer  : ", info.Manufact)
		log.Println("\tProduct       : ", info.Product)
		log.Println("\tSerial        : ", info.Serial)
		log.Println("\tHave Serial   : ", info.HaveSerial)
		log.Println("\tEnable IR     : ", info.EnableIR)
		log.Println("\tRemote Wakeup : ", info.RemoteWakeup)
	}

	ppm, err := kal.Kal((*kal.Context)(dev), kal.GSM850)
	log.Printf("PPM: %d\n", ppm)
	log.Printf("err: %s\n", err)
}
