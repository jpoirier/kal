bin_PROGRAMS = kal

kal_SOURCES = \
   arfcn_freq.cpp \
   c0_detect.cpp	 \
   circular_buffer.cpp \
   fcch_detector.cpp \
   kal.cpp \
   offset.cpp \
   usrp_source.cpp \
   util.cpp \
   arfcn_freq.h \
   c0_detect.h \
   circular_buffer.h \
   fcch_detector.h \
   offset.h \
   usrp_complex.h \
   usrp_source.h \
   util.h\
   version.h

kal_CXXFLAGS = $(FFTW3_CFLAGS) $(LIBRTLSDR_CFLAGS)
kal_LDADD = $(FFTW3_LIBS) $(LIBRTLSDR_LIBS) -lrt
