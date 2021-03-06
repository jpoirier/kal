# libfftw3 must be configured via> ./configure --enable-shared
CFLAGS=-std=c++11 -O2 -g -Wall -W
LDLIBS+=-lrtlsdr -lfftw3 -lm -lrt
CC=g++


all: kal libkal install libgokal

kal: src/kal.cpp src/arfcn_freq.cpp src/c0_detect.cpp src/circular_buffer.cpp src/fcch_detector.cpp src/usrp_source.cpp src/offset.cpp src/util.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

libkal: src/libkal.cpp src/arfcn_freq.cpp src/c0_detect.cpp src/circular_buffer.cpp src/fcch_detector.cpp src/usrp_source.cpp src/offset.cpp src/util.cpp
	$(CC) $(CFLAGS) -fPIC -shared -o libkal.so $^ $(LDFLAGS) $(LDLIBS)

libgokal:
	go build -v -o kal.a kal.go

install:
	sudo cp -f libkal.so /usr/local/lib
	sudo ldconfig

clean:
	rm -f *~ *.o src/*.o kal libkal.so kal.a



