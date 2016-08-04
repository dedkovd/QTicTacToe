#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include <QSettings>
#include <QNetworkInterface>

#include "gamesettingsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    board = new QTicTacToeBoard(ui->scrollArea, 2);
    ui->scrollArea->setWidget(board);

    ui->actionNew_game->setIcon(QIcon::fromTheme("document-new"));
    ui->actionGame_settings->setIcon(QIcon::fromTheme("document-properties"));

    game = 0;
    tcpServer = 0;
    tcpSocket = 0;
    clientSocket = 0;

    isServer = false;
    isClient = false;
    isLocalGame = true;

    newGame();
}

void MainWindow::newGame()
{
    if (isClient)
    {
        QMessageBox::information(this,tr("QTicTacToe"),tr("You connected to server! Only server can start game!"));
        return;
    }

    if (game) delete game;

    QSettings settings("Home inc.","TicTacToe",this);
    settings.beginGroup("gameSettings");
    boardSize = settings.value("boardSize",3).toInt();
    countToWin = settings.value("countToWin",3).toInt();

    game = new QTicTacToeGame(boardSize,countToWin,this);
    board->setGame(game);

    connect(game,SIGNAL(gameOver(int)), this, SLOT(gameOver(int)));
    connect(game,SIGNAL(itemPuted(int,int,int)), this, SLOT(turn(int,int,int)));

    if (isServer)
    {
        clientSocket->write(QString("settings:%1:%2").arg(boardSize).arg(countToWin).toUtf8());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::gameOver(int player)
{
    QString mess(player?tr("Game over! Player %1 win!").arg(player):tr("Game over! No win!"));
    QMessageBox::information(this,tr("Game over"),mess);

    game->clear();
}

void MainWindow::turn(int x, int y, int player)
{
    QString data = QString("%1:%2:%3").arg(x).arg(y).arg(player);
    if (isServer)
    {
        clientSocket->write(data.toUtf8());
    }
    if (isClient)
    {
        tcpSocket->write(data.toUtf8());
    }
    this->statusBar()->showMessage(tr("Opponent turn"));
}

void MainWindow::readTurn()
{
    QString data = QString::fromUtf8(isClient?tcpSocket->readAll():clientSocket->readAll());

    QStringList t = data.split(":");

    if (t.at(0) == "settings")
    {
        delete game;
        game = new QTicTacToeGame(t.at(1).toInt(), t.at(2).toInt(), this);
        board->setGame(game);

        connect(game,SIGNAL(gameOver(int)), this, SLOT(gameOver(int)));
        connect(game,SIGNAL(itemPuted(int,int,int)), this, SLOT(turn(int,int,int)));

        ui->actionStart_server->setEnabled(false);
        ui->actionConnect_to_Server->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);

        this->statusBar()->showMessage(tr("Connected to server!"), 5000);
    } else
    {
        if (game->put(t.at(0).toInt(), t.at(1).toInt(), t.at(2).toInt()))
        {
            this->statusBar()->showMessage(tr("Your turn"));
        }
    }
}

void MainWindow::on_actionNew_game_triggered()
{
    newGame();
}

void MainWindow::on_actionGame_settings_triggered()
{
    GameSettingsDialog *dialog = new GameSettingsDialog(this);

    dialog->setBoardSize(boardSize);
    dialog->setCountToWin(countToWin);

    if (dialog->exec())
    {
        QSettings settings("Home inc.","TicTacToe",this);
        settings.beginGroup("gameSettings");
        settings.setValue("boardSize",dialog->getBoardSize());
        settings.setValue("countToWin", dialog->getCountToWin());
        newGame();
    }

    delete dialog;
}

void MainWindow::on_actionStart_server_triggered()
{
    tcpServer = new QTcpServer(this);
    tcpServer->setMaxPendingConnections(1);

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnection()));

    if (!tcpServer->listen(QHostAddress::Any, 1515)) {
        QMessageBox::critical(this, tr("QTicTacToe Server"), tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
        return;
    }

    board->setBoardPlayer(1);

    this->statusBar()->showMessage(tr("Waiting for connection"));
    ui->actionStart_server->setEnabled(false);
    ui->actionConnect_to_Server->setEnabled(false);
    ui->actionDisconnect->setEnabled(true);
    board->setEnabled(false);

    isClient = false;
    isLocalGame = false;
    isServer = true;
}

void MainWindow::newConnection()
{
    this->statusBar()->showMessage(tr("New player connected!"), 5000);

    clientSocket = tcpServer->nextPendingConnection();

    connect(clientSocket,SIGNAL(readyRead()),this, SLOT(readTurn()));
    connect(clientSocket,SIGNAL(disconnected()),clientSocket,SLOT(deleteLater()));
    connect(clientSocket,SIGNAL(disconnected()),this,SLOT(on_actionDisconnect_triggered()));

    newGame();
    board->setEnabled(true);
}

void MainWindow::on_actionConnect_to_Server_triggered()
{
    tcpSocket = new QTcpSocket(this);
    tcpSocket->abort();

    QString address = QInputDialog::getText(this,tr("QTicTacToe"),tr("Address"));

    if (address.length()>0)    {
        tcpSocket->connectToHost(address,1515);

        isClient = true;
        isLocalGame = false;
        isServer = false;

        connect(tcpSocket,SIGNAL(readyRead()),this, SLOT(readTurn()));
        connect(tcpSocket,SIGNAL(disconnected()),tcpSocket,SLOT(deleteLater()));
        connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(on_actionDisconnect_triggered()));

        board->setBoardPlayer(2);
    }
}

void MainWindow::on_actionDisconnect_triggered()
{
    if (isServer)
    {
        disconnect(clientSocket,SIGNAL(disconnected()),this,SLOT(on_actionDisconnect_triggered()));
        clientSocket->disconnectFromHost();
        tcpServer->close();
    }
    if (isClient)
    {
        disconnect(tcpSocket,SIGNAL(disconnected()),this,SLOT(on_actionDisconnect_triggered()));
        tcpSocket->disconnectFromHost();
    }

    isClient = false;
    isLocalGame = true;
    isServer = false;

    ui->actionDisconnect->setEnabled(false);
    ui->actionConnect_to_Server->setEnabled(true);
    ui->actionStart_server->setEnabled(true);
    board->setEnabled(true);

    board->setBoardPlayer(0);
    newGame();

    this->statusBar()->clearMessage();
    this->statusBar()->showMessage(tr("Player disconnected!"), 5000);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About"), tr("QTicTacToe v 0.1"));
}


