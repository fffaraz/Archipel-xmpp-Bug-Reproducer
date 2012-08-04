#-------------------------------------------------
#
# Project created by QtCreator 2012-07-15T09:53:23
#
#-------------------------------------------------

QT       += core gui network xml

TARGET = xmppTester
TEMPLATE = app

include(base/base.pri)
include(client/client.pri)

INCLUDEPATH += base
INCLUDEPATH += client

DESTDIR = ../bin
OBJECTS_DIR = ../tmp/.obj
MOC_DIR = ../tmp/.moc
RCC_DIR = ../tmp/.rcc
UI_DIR = ../tmp/.ui



SOURCES += main.cpp\
        mainwindow.cpp \
    xmppclient.cpp \
    dialoglogin.cpp \
    windowmain.cpp \
    windowiq.cpp

HEADERS  += mainwindow.h \
    xmppclient.h \
    dialoglogin.h \
    windowmain.h \
    windowiq.h

FORMS    += mainwindow.ui \
    dialoglogin.ui \
    windowmain.ui \
    windowiq.ui

















