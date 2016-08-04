#-------------------------------------------------
#
# Project created by QtCreator 2011-02-12T15:39:17
#
#-------------------------------------------------

QT       += core gui network widgets

TARGET = QTicTacToe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qtictactoegame.cpp \
    qtictactoeboard.cpp \
    gamesettingsdialog.cpp

HEADERS  += mainwindow.h \
    qtictactoegame.h \
    qtictactoeboard.h \
    gamesettingsdialog.h

FORMS    += mainwindow.ui \
    gamesettingsdialog.ui

RESOURCES += \
    images.qrc

TRANSLATIONS += tictactoe_ru.ts

#INCLUDEPATH += ../../qxmpp-0.2.0/src

#LIBS += -L../../qxmpp-0.2.0/lib -lqxmpp

#OTHER_FILES += \
#    Board.qml
