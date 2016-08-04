#ifndef QTICTACTOEBOARD_H
#define QTICTACTOEBOARD_H

#include <QtWidgets/QWidget>
#include "qtictactoegame.h"

const int cellSize = 50;

class QTicTacToeBoard : public QWidget
{
    Q_OBJECT
public:
    explicit QTicTacToeBoard(QWidget *parent = 0, int playersCount = 2);
    void setGame(QTicTacToeGame *game);

    void setBoardPlayer(int player);    

private:
    QTicTacToeGame *game;

    void paintEvent(QPaintEvent *);
    QSize sizeHint();
    void mousePressEvent(QMouseEvent *);

    int currPlayer;
    int boardPlayer;
    int playersCount;

private slots:
    void turn(int x, int y, int player);
};

#endif // QTICTACTOEBOARD_H
