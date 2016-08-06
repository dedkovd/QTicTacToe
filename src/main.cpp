#include <QtWidgets/QApplication>
#include "mainwindow.h"

#include <QTranslator>
#include <QLocale>
#include <QDir>
#include "qtictactoegame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dir(QApplication::applicationDirPath());
    dir.cd("i18n");

    QTranslator translator,qt;
    translator.load("tictactoe_"+QLocale::system().name(),dir.absolutePath());
    a.installTranslator(&translator);
    qt.load("qt_"+QLocale::system().name(),dir.absolutePath());
    a.installTranslator(&qt);

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
