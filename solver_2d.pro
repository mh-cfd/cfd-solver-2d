TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    globals.cpp \
    Main.cpp \
    phi_mult.cpp

HEADERS += \
    phi_mult.h \
    globals.h

LIBS+=  -lOpenGL32 -lGLU32 -lglut32

