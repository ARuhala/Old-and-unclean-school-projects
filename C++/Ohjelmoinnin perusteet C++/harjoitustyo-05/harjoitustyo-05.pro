TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tiedostonluku.cpp \
    ksl_lista.cpp \
    materiaalilista.cpp

HEADERS += \
    tiedostonluku.hh \
    ksl_lista.hh \
    materiaalilista.hh
