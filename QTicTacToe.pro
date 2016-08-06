#-------------------------------------------------
#
# Project created by QtCreator 2011-02-12T15:39:17
#
#-------------------------------------------------

QT       += core gui network widgets

TARGET = QTicTacToe
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/qtictactoegame.cpp \
    src/qtictactoeboard.cpp \
    src/gamesettingsdialog.cpp

HEADERS  += src/mainwindow.h \
    src/qtictactoegame.h \
    src/qtictactoeboard.h \
    src/gamesettingsdialog.h

FORMS    += ui/mainwindow.ui \
    ui/gamesettingsdialog.ui

RESOURCES += \
    resources/images.qrc

TRANSLATIONS += i18n/tictactoe_ru.ts
