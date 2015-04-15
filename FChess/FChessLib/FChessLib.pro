#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T13:26:09
#
#-------------------------------------------------

QT       -= gui

TARGET = FChessLib
TEMPLATE = lib

DEFINES += FCHESSLIB_LIBRARY

SOURCES += fchesslib.cpp \
    Data/board.cpp

HEADERS += fchesslib.h\
        fchesslib_global.h \
    Data/board.h \
    Data/CommonData.h \
    Factory/puppetfactory.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
