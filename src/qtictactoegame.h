#ifndef QTICTACTOEGAME_H
#define QTICTACTOEGAME_H

#include <QObject>

class QTicTacToeGame : public QObject
{
    Q_OBJECT
public:
    explicit QTicTacToeGame(int size = 3, int countToWin = 3, QObject *parent = 0);
    bool put(int x, int y, int player);
    int getPlayer(int x, int y);
    Q_INVOKABLE int getSize();
    void clear();

private:
    int **board;
    int size, countToWin, aviableCells;

    bool checkFromPoint(int x, int y);

signals:
    void gameOver(int player);
    void itemPuted(int x, int y, int player);

public slots:

};

#endif // QTICTACTOEGAME_H
