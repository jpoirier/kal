TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/arfcn_freq.cpp \
    ../src/c0_detect.cpp \
    ../src/circular_buffer.cpp \
    ../src/fcch_detector.cpp \
    ../src/kal.cpp \
    ../src/offset.cpp \
    ../src/usrp_source.cpp \
    ../src/util.cpp

HEADERS += \
    ../src/arfcn_enums.h \
    ../src/arfcn_freq.h \
    ../src/c0_detect.h \
    ../src/circular_buffer.h \
    ../src/fcch_detector.h \
    ../src/kal.h \
    ../src/offset.h \
    ../src/usrp_complex.h \
    ../src/usrp_source.h \
    ../src/util.h \
    ../src/version.h

