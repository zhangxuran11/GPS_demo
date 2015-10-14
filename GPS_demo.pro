#-------------------------------------------------
#
# Project created by QtCreator 2015-08-21T09:31:34
#
#-------------------------------------------------

QT       += core gui

TARGET = GPS_demo
TEMPLATE = app
include(GPS_Driver/GPS_Driver.pri)
SOURCES += main.cpp\
        mainwindow.cpp \


HEADERS  += mainwindow.h \


FORMS    += mainwindow.ui



DEFINES += $$(ARCH)
contains( DEFINES,arm ) {
    mytarget.commands = scp ./${TARGET} root@192.168.1.30:/
}

mytarget.target = a

mytarget.depends = all



QMAKE_EXTRA_TARGETS += mytarget
