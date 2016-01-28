#-------------------------------------------------
#
# Project created by QtCreator 2016-01-26T19:53:31
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = ArduinoSonar
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    arducomm.cpp

HEADERS  += widget.h \
    arducomm.h

FORMS    += widget.ui
