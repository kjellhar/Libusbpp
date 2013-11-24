#-------------------------------------------------
#
# Project created by QtCreator 2013-11-23T14:56:01
#
#-------------------------------------------------

QT       -= gui

TARGET = QLibUsb
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    usb.cpp \
    usbimpl.cpp

HEADERS += \
    usb.h \
    usbimpl.h


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
