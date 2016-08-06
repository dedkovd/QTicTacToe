#include "qtictactoeboard.h"
#include <QPainter>
#include <QMouseEvent>

QTicTacToeBoard::QTicTacToeBoard(QWidget *parent, int playersCount) :
    QWidget(parent)
{
    currPlayer = 1;
    boardPlayer = 0;
    this->playersCount = playersCount;
}

void QTicTacToeBoard::setBoardPlayer(int player)
{
    boardPlayer = player;
    currPlayer = 1;
}

void QTicTacToeBoard::setGame(QTicTacToeGame *game)
{
    this->game = game;
    setGeometry(0,0,game->getSize()*cellSize,game->getSize()*cellSize);

    connect(game,SIGNAL(itemPuted(int,int,int)), this, SLOT(turn(int,int,int)));

    update();
}

void QTicTacToeBoard::turn(int /*x*/, int /*y*/, int /*player*/)
{
    currPlayer = (currPlayer == playersCount?1:currPlayer+1);

    update();
}

QSize QTicTacToeBoard::sizeHint()
{
    if (game)
        return QSize(game->getSize()*cellSize, game->getSize()*cellSize);
    else
        return QSize(0,0);
}

void QTicTacToeBoard::mousePressEvent(QMouseEvent *event)
{
    if (boardPlayer && currPlayer != boardPlayer) return;

    int x = event->x() / cellSize;
    int y = event->y() / cellSize;

    game->put(x,y,currPlayer);
}

void QTicTacToeBoard::paintEvent(QPaintEvent *)
{
    if (!game) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::darkGreen, 1));

    int size = game->getSize();

    for (int i=1; i<size; i++)
    {
        painter.drawLine(i*cellSize,0,i*cellSize,this->height());
        painter.drawLine(0,i*cellSize,this->width(),i*cellSize);
    }

    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size;j++)
        {
            int player = game->getPlayer(i,j);

            if (player)
            {
                painter.drawImage(i*cellSize, j*cellSize, QImage(QString(":/%1").arg(player)));
            }
        }
    }
}
