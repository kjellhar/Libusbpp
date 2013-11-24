#-------------------------------------------------
#
# Project created by QtCreator 2013-11-23T14:56:01
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = QLibUsb
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    usb.cpp \
    device.cpp

HEADERS += \
    usb.h \
    device.h


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}


LIBS += "/usr/local/lib/libusb-1.0.dylib"

INCLUDEPATH += "/usr/local/include/libusb-1.0"
