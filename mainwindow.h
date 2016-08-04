#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

#include "qtictactoegame.h"
#include "qtictactoeboard.h"

//#include <QXmppClient.h>
//#include <QXmppMessage.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QTicTacToeGame *game;
    QTicTacToeBoard *board;

    QTcpServer *tcpServer;

    QTcpSocket *tcpSocket;
    QTcpSocket *clientSocket;

    void newGame();
    int boardSize;
    int countToWin;

    bool isServer;
    bool isClient;
    bool isLocalGame;

private slots:
    void on_actionAbout_triggered();
    void on_actionDisconnect_triggered();
    void on_actionConnect_to_Server_triggered();
    void on_actionStart_server_triggered();
    void on_actionGame_settings_triggered();
    void on_actionNew_game_triggered();
    void gameOver(int player);
    void newConnection();

    void turn(int x, int y, int player);
    void readTurn();
};

#endif // MAINWINDOW_H
