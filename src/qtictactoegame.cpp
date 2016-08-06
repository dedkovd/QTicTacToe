#include "qtictactoegame.h"

QTicTacToeGame::QTicTacToeGame(int size, int countToWin, QObject *parent) :
    QObject(parent)
{
    board = new int*[size];
    for (int i=0; i<size; i++)
        board[i] = new int[size];

    this->size = size;
    this->countToWin = countToWin;

    clear();
}

void QTicTacToeGame::clear()
{
    aviableCells = size*size;

    for (int i=0; i<size;i++)
        for (int j=0; j<size; j++)
            board[i][j] = 0;
}

bool QTicTacToeGame::put(int x, int y, int player)
{
    if (x<0||y<0||x>=size||y>=size) return false;

    if (board[x][y]) return false;

    board[x][y] = player;

    emit itemPuted(x,y, player);

    if (checkFromPoint(x,y)) emit gameOver(player);

    aviableCells--;

    if (!aviableCells)
        emit gameOver(0);

    return true;
}

bool QTicTacToeGame::checkFromPoint(int x, int y)
{
    int currPlayer = board[x][y];
    int cnt = 0;

    int minXBorder = qMax(x-countToWin,0);
    int maxXBorder = qMin(x+countToWin,size);
    int minYBorder = qMax(y-countToWin,0);
    int maxYBorder = qMin(y+countToWin,size);

    // check X axis
    for (int i=minXBorder; i<maxXBorder; i++)
    {
        if (board[i][y]==currPlayer) cnt++;
        else cnt=0;

        if (cnt==countToWin) return true;
    }

    // check Y axis
    cnt = 0;
    for (int i=minYBorder; i<maxYBorder; i++)
    {
        if (board[x][i]==currPlayer) cnt++;
        else cnt=0;

        if (cnt==countToWin) return true;
    }

    int vX = x;
    int vY = y;
    cnt = 0;

    // check TopLeft - BottomRight diag
    while (vX >= 0 && vX >= x-countToWin && vY >=0 && vY >= y-countToWin && board[vX][vY] == currPlayer)
    {
        cnt++; vX--; vY--;
    }
    vX = x; vY = y; cnt--;
    while (vX < size && vX < x+countToWin && vY < size && vY < y+countToWin && board[vX][vY] == currPlayer)
    {
        cnt++; vX++; vY++;
    }
    if (cnt>=countToWin) return true;

    // check BottomLeft - TopRight diag
    vX = x; vY = y; cnt = 0;
    while (vX >= 0 && vX >= x-countToWin && vY < size && vY < y+countToWin && board[vX][vY] == currPlayer)
    {
        cnt++; vX--; vY++;
    }
    vX = x; vY = y; cnt--;
    while (vX < size && vX < x+countToWin && vY >=0 && vY >= y-countToWin && board[vX][vY] == currPlayer)
    {
        cnt++; vX++; vY--;
    }
    if (cnt>=countToWin) return true;

    return false;
}

int QTicTacToeGame::getPlayer(int x, int y)
{
    Q_ASSERT(x>=0&&y>=0&&x<size&&y<size);

    return board[x][y];
}

int QTicTacToeGame::getSize()
{
    return size;
}
