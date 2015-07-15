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
    exceptions.cpp \
    Factories/figurefactory.cpp \
    Interfaces/figure.cpp \
    Visual/boardrendererimpl.cpp \
    Facade/gameplayfacade.cpp \
    Interfaces/player.cpp \
    Factories/playerfactory.cpp \
    gameplayobserver.cpp

HEADERS  += mainwindow.h \
    board.h \
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
    exceptions.h \
    Factories/figurefactory.h \
    Interfaces/figure.h \
    Interfaces/BoardRendererInterface.h \
    Visual/boardrendererimpl.h \
    Facade/gameplayfacade.h \
    Interfaces/player.h \
    Factories/playerfactory.h \
    gameplayobserver.h

FORMS    += mainwindow.ui \
    networkSettings.ui

RESOURCES += \
    icons.qrc
