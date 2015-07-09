#-------------------------------------------------
#
# Project created by QtCreator 2012-04-03T19:14:48
#
#-------------------------------------------------

QT       += core gui network widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    figure.cpp \
    player.cpp \
    rules.cpp \
    Figures/rook.cpp \
    Figures/pawn.cpp \
    Figures/bishop.cpp \
    Figures/knight.cpp \
    Figures/king.cpp \
    Figures/queen.cpp \
    Players/human.cpp \
    Visual/display.cpp \
    Defines.cpp \
    evaluator.cpp \
    Visual/figureselector.cpp \
    Players/tcpiplayer.cpp \
    messageinterface.cpp \
    exceptions.cpp

HEADERS  += mainwindow.h \
    board.h \
    figure.h \
    player.h \
    rules.h \
    Defines.h \
    Figures/rook.h \
    Figures/pawn.h \
    Figures/bishop.h \
    Figures/knight.h \
    Figures/king.h \
    Figures/queen.h \
    Players/human.h \
    Visual/display.h \
    evaluator.h \
    Visual/figureselector.h \
    Players/tcpiplayer.h \
    messageinterface.h \
    exceptions.h

FORMS    += mainwindow.ui \
    networkSettings.ui
