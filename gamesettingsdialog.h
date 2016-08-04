#ifndef GAMESETTINGSDIALOG_H
#define GAMESETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class GameSettingsDialog;
}

class GameSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameSettingsDialog(QWidget *parent = 0);
    ~GameSettingsDialog();

    int getBoardSize();
    int getCountToWin();

    void setBoardSize(int size);
    void setCountToWin(int count);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::GameSettingsDialog *ui;

private slots:
    void on_sbBoardSize_valueChanged(int );
};

#endif // GAMESETTINGSDIALOG_H
