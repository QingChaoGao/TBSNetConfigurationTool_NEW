#-------------------------------------------------
#
# Project created by QtCreator 2017-11-21T18:38:15
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = TBSNetConfigurationTool
TEMPLATE    = app
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR     = $$PWD/../bin

SOURCES     += main.cpp \
    tbsfunc.cpp \
    threadtbs.cpp \
    mymesg.cpp 

SOURCES     += iconhelper.cpp
SOURCES     += appinit.cpp
SOURCES     += hdmioptiongui.cpp

HEADERS     += iconhelper.h \
    tbsfunc.h \
    threadtbs.h \
    mymesg.h 

HEADERS     += appinit.h
HEADERS     += hdmioptiongui.h

FORMS       += hdmioptiongui.ui \
    mymesg.ui

RESOURCES   += main.qrc
RESOURCES   += qss.qrc
CONFIG      += qt warn_off
INCLUDEPATH += $$PWD
#LIBS        +=-lpthread -ldl $$PWD/libpci.so
RC_FILE = hdmioptiongui.rc
#DEFINES += QT_NO_WARNING_OUTPUT\
 #                QT_NO_DEBUG_OUTPUT


