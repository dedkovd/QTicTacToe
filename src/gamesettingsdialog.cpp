#include "gamesettingsdialog.h"
#include "ui_gamesettingsdialog.h"

GameSettingsDialog::GameSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameSettingsDialog)
{
    ui->setupUi(this);
}

GameSettingsDialog::~GameSettingsDialog()
{
    delete ui;
}

void GameSettingsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void GameSettingsDialog::on_sbBoardSize_valueChanged(int value)
{
    ui->sbCountToWin->setMaximum(value);
}

int GameSettingsDialog::getBoardSize()
{
    return ui->sbBoardSize->value();
}

int GameSettingsDialog::getCountToWin()
{
    return ui->sbCountToWin->value();
}

void GameSettingsDialog::setBoardSize(int size)
{
    ui->sbBoardSize->setValue(size);
}

void GameSettingsDialog::setCountToWin(int count)
{
    ui->sbCountToWin->setValue(count);
}
