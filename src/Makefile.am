bin_PROGRAMS = kal

kal_SOURCES = \
   arfcn_freq.c \
   c0_detect.c	 \
   circular_buffer.c \
   fcch_detector.c \
   kal.c \
   offset.c \
   usrp_source.c \
   util.c \
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
