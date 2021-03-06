#-------------------------------------------------
#
# Project created by QtCreator 2012-04-03T19:14:48
#
#-------------------------------------------------

QT       += core gui network widgets core5compat

TARGET = Chess
TEMPLATE = app

SOURCES += main.cpp\
    Utils/timer.cpp \
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
    Visual/playerlayer.cpp \
    Observers/gameplayobserver.cpp \
    Observers/visualobserver.cpp \
    Utils/utility.cpp \
    Utils/validator.cpp \
    Proxy/visualproxy.cpp \
    Players/computer.cpp \
    AI/data.cpp \
    Figures/whitepawn.cpp \
    Figures/blackpawn.cpp \
    AI/aiboard.cpp \
    Utils/boardfilter.cpp \
    AI/decisiontree.cpp \
    AI/Strategies/randomstrategy.cpp \
    AI/Strategies/minmaxstrategy.cpp \
    AI/aiEvaluator.cpp \
    Facade/uifacade.cpp \
    Observers/messenger.cpp \

HEADERS  += mainwindow.h \
    Utils/timer.h \
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
    Interfaces/RenderObject.h \
    Visual/playerlayer.h \
    Observers/gameplayobserver.h \
    Observers/visualobserver.h \
    Interfaces/singleton.h \
    Interfaces/LayerInterface.h \
    Utils/utility.h \
    Utils/validator.h \
    Proxy/visualproxy.h \
    Players/computer.h \
    AI/data.h \
    Figures/whitepawn.h \
    Figures/blackpawn.h \
    Interfaces/IBoard.h \
    AI/aiboard.h \
    Utils/boardfilter.h \
    AI/decisiontree.h \
    AI/IStrategy.h \
    AI/Strategies/randomstrategy.h \
    AI/Strategies/minmaxstrategy.h \
    AI/aiEvaluator.h \
    Facade/uifacade.h \
    Observers/messenger.h \
    Interfaces/iserializable.h

FORMS    += mainwindow.ui \
    networkSettings.ui \
    newGameDialog.ui

RESOURCES += \
    icons.qrc
