#-------------------------------------------------
#
# Project created by QtCreator 2015-08-21T09:31:34
#
#-------------------------------------------------

QT       += core gui

TARGET = GPS_demo
TEMPLATE = app
include(qextserialport/src/qextserialport.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    gprmc.cpp \


HEADERS  += mainwindow.h \
    gprmc.h \


FORMS    += mainwindow.ui



