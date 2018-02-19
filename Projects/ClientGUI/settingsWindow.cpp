#include "settingsWindow.h"
#include "ui_settingsWindow.h"

settingsWindow::settingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsWindow)
{
    ui->setupUi(this);
}

settingsWindow::~settingsWindow()
{
    delete ui;
}
