#-------------------------------------------------
#
# Project created by QtCreator 2014-02-24T11:32:03
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = WienerFilter
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    wienerfilter.cpp \
    gaussfilter.cpp

LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui

HEADERS += \
    wienerfilter.h \
    gaussfilter.h

