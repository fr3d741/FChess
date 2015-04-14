#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T10:38:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FChessApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Widgets/boardwidget.cpp

HEADERS  += mainwindow.h \
    Widgets/boardwidget.h

FORMS    += mainwindow.ui
