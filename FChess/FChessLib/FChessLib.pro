#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T13:26:09
#
#-------------------------------------------------

QT       -= gui

TARGET = FChessLib
TEMPLATE = lib

DEFINES += FCHESSLIB_LIBRARY

SOURCES += fchesslib.cpp

HEADERS += fchesslib.h\
        fchesslib_global.h \
    Data/Puppets.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
